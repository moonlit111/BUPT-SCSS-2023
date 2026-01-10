from flask import Flask, render_template, request, jsonify, session, redirect, url_for
from werkzeug.security import generate_password_hash, check_password_hash
from fido2.server import Fido2Server
from fido2.webauthn import PublicKeyCredentialRpEntity, PublicKeyCredentialUserEntity, PublicKeyCredentialDescriptor
from fido2.utils import websafe_encode, websafe_decode
import os
import json
import base64

# 启用 WebAuthn JSON 映射
import fido2.features
fido2.features.webauthn_json_mapping.enabled = True

app = Flask(__name__)
app.secret_key = os.urandom(24)

# 配置 RP Entity，使用正确的 origin
rp = PublicKeyCredentialRpEntity(id="localhost", name="Example App")

# 定义 origin 验证函数
def verify_origin(origin):
    # 允许 localhost 的所有端口
    return origin in ["http://localhost:5000", "https://localhost:5000"]

# 创建 Fido2Server，指定 origin 验证函数
server = Fido2Server(rp, attestation="none", verify_origin=verify_origin)

# 全局用户存储（实际应用应使用数据库）
users = {}

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        if username in users:
            return "User already exists", 400
        hashed_password = generate_password_hash(password)
        users[username] = {"password": hashed_password, "credentials": None}
        return redirect(url_for("fido_setup", username=username))
    return render_template("register.html")

@app.route("/fido_setup/<username>", methods=["GET"])
def fido_setup(username):
    if username not in users:
        return "User not found", 404
    return render_template("fido_setup.html", username=username)

@app.route("/fido_register", methods=["POST"])
def fido_register():
    username = request.form.get("username")
    if not username or username not in users:
        return jsonify({"error": "User not found"}), 404

    try:
        user_entity = PublicKeyCredentialUserEntity(
            id=username.encode(),
            name=username,
            display_name=username
        )
        registration_data, state = server.register_begin(user_entity)

        # 存储状态到会话
        session["fido_registration_state"] = state

        # 将 registration_data 转换为可序列化的格式
        # registration_data 是 CredentialCreationOptions 对象
        pk = registration_data.public_key

        # 使用标准 Base64 编码（不是 websafe）
        challenge = base64.b64encode(pk.challenge).decode()
        user_id = base64.b64encode(pk.user.id).decode()

        response_data = {
            "publicKey": {
                "challenge": challenge,
                "rp": {
                    "name": pk.rp.name,
                    "id": pk.rp.id
                },
                "user": {
                    "id": user_id,
                    "name": pk.user.name,
                    "displayName": pk.user.display_name
                },
                "pubKeyCredParams": [
                    {"type": "public-key", "alg": param.alg}
                    for param in pk.pub_key_cred_params
                ],
                "timeout": 60000,
                "attestation": "direct"
            }
        }
        return jsonify(response_data)
    except Exception as e:
        import traceback
        traceback.print_exc()
        return jsonify({"error": str(e)}), 400

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        if username not in users or not check_password_hash(users[username]["password"], password):
            return "Invalid username or password", 400
        session["username"] = username
        return redirect(url_for("fido_auth"))
    return render_template("login.html")

@app.route("/fido_auth", methods=["GET"])
def fido_auth():
    username = session.get("username")
    if not username or username not in users:
        return "Unauthorized", 401

    if users[username].get("credentials") is None:
        return "User has no FIDO2 credentials", 400

    try:
        # 解析存储的凭证
        cred_data = json.loads(users[username]["credentials"])
        credential_id = base64.b64decode(cred_data["credential_id"])

        # 创建凭证描述符
        credential_descriptor = PublicKeyCredentialDescriptor(
            type="public-key",
            id=credential_id
        )

        # 开始认证
        authentication_data, state = server.authenticate_begin([credential_descriptor])
        session["fido_authentication_state"] = state

        # 将 authentication_data 转换为可序列化的格式
        pk = authentication_data.public_key

        # 使用标准 Base64 编码
        challenge = base64.b64encode(pk.challenge).decode()
        cred_id_encoded = base64.b64encode(credential_id).decode()

        response_data = {
            "publicKey": {
                "challenge": challenge,
                "timeout": 60000,
                "rpId": pk.rp_id,
                "userVerification": "preferred",
                "allowCredentials": [
                    {
                        "type": "public-key",
                        "id": cred_id_encoded
                    }
                ]
            }
        }

        return jsonify(response_data)
    except Exception as e:
        import traceback
        traceback.print_exc()
        return jsonify({"error": str(e)}), 400

@app.route("/fido_complete_register", methods=["POST"])
def fido_complete_register():
    data = request.get_json()
    username = data.get("username")

    if not username or username not in users:
        return jsonify({"error": "User not found"}), 404

    try:
        # 获取存储的注册状态
        state = session.pop("fido_registration_state", None)
        if not state:
            return jsonify({"error": "Registration state not found"}), 400

        print("Received data:", json.dumps(data, indent=2))

        # 使用正确的导入
        from fido2.webauthn import CollectedClientData, AttestationObject

        # 解码 Base64 数据
        client_data_bytes = base64.b64decode(data["response"]["clientDataJSON"])
        attestation_object_bytes = base64.b64decode(data["response"]["attestationObject"])

        print("Client data bytes length:", len(client_data_bytes))
        print("Attestation object bytes length:", len(attestation_object_bytes))

        # 创建对象
        client_data = CollectedClientData(client_data_bytes)
        attestation_object = AttestationObject(attestation_object_bytes)

        print("Client data:", client_data)
        print("Client data origin:", client_data.origin)
        print("Attestation object:", attestation_object)

        # 完成注册
        auth_data = server.register_complete(
            state,
            client_data,
            attestation_object
        )

        print("Auth data:", auth_data)
        print("Auth data type:", type(auth_data))
        print("Auth data credential_data:", auth_data.credential_data)

        # 存储凭证数据（使用标准 Base64）
        # auth_data 是 AuthenticatorData 对象
        # credential_id 在 credential_data 属性中
        cred_id = base64.b64encode(auth_data.credential_data.credential_id).decode()
        # 存储公钥
        from fido2 import cbor
        public_key = auth_data.credential_data.public_key
        public_key_bytes = cbor.encode(public_key)

        users[username]["credentials"] = json.dumps({
            "credential_id": cred_id,
            "public_key": base64.b64encode(public_key_bytes).decode()
        })

        return jsonify({"status": "registered"})
    except Exception as e:
        import traceback
        traceback.print_exc()
        return jsonify({"error": str(e)}), 400

@app.route("/fido_login", methods=["POST"])
def fido_login():
    username = session.get("username")
    if not username or username not in users:
        return jsonify({"error": "Unauthorized"}), 401

    data = request.get_json()
    try:
        # 获取存储的认证状态
        state = session.pop("fido_authentication_state", None)
        if not state:
            return jsonify({"error": "Authentication state not found"}), 400

        # 解析存储的凭证
        cred_data = json.loads(users[username]["credentials"])
        stored_cred_id = base64.b64decode(cred_data["credential_id"])

        # 解码公钥
        from fido2 import cbor
        public_key_bytes = base64.b64decode(cred_data["public_key"])
        public_key = cbor.decode(public_key_bytes)

        print("Received login data:", json.dumps(data, indent=2))
        print("Stored credential ID:", stored_cred_id.hex())
        print("Stored public key:", public_key)

        # 使用正确的导入
        from fido2.webauthn import CollectedClientData, AuthenticatorData, AttestedCredentialData

        # 解码 Base64 数据
        credential_id = base64.b64decode(data["id"])
        client_data_bytes = base64.b64decode(data["response"]["clientDataJSON"])
        authenticator_data_bytes = base64.b64decode(data["response"]["authenticatorData"])
        signature = base64.b64decode(data["response"]["signature"])

        print("Credential ID from client:", credential_id.hex())
        print("Client data bytes length:", len(client_data_bytes))
        print("Authenticator data bytes length:", len(authenticator_data_bytes))
        print("Signature length:", len(signature))

        # 创建对象
        client_data = CollectedClientData(client_data_bytes)
        authenticator_data = AuthenticatorData(authenticator_data_bytes)

        print("Client data:", client_data)
        print("Client data origin:", client_data.origin)
        print("Authenticator data:", authenticator_data)

        # 重建 AttestedCredentialData 对象用于验证
        # 我们需要创建一个包含 credential_id 和 public_key 的对象
        from fido2.webauthn import Aaguid
        attested_cred_data = AttestedCredentialData.create(
            aaguid=Aaguid.NONE,
            credential_id=stored_cred_id,
            public_key=public_key
        )

        # 完成认证
        server.authenticate_complete(
            state,
            [attested_cred_data],
            credential_id,
            client_data,
            authenticator_data,
            signature
        )

        session["authenticated"] = True
        return jsonify({"status": "authenticated"})
    except Exception as e:
        import traceback
        traceback.print_exc()
        return jsonify({"error": str(e)}), 400

@app.route("/", methods=["GET"])
def index():
    if session.get("authenticated"):
        return redirect(url_for("dashboard"))
    return render_template("index.html")

@app.route("/dashboard", methods=["GET"])
def dashboard():
    if not session.get("authenticated"):
        return redirect(url_for("login"))
    username = session.get("username")
    return render_template("dashboard.html", username=username)

@app.route("/logout", methods=["GET"])
def logout():
    session.clear()
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run(debug=True, host="localhost", port=5000)