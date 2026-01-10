/**
 * FIDO2 认证辅助函数
 */

// 检查浏览器是否支持 WebAuthn
function isFido2Supported() {
    return window.PublicKeyCredential !== undefined &&
           navigator.credentials !== undefined;
}

// 将 ArrayBuffer 转换为 Base64 字符串
function arrayBufferToBase64(buffer) {
    let binary = '';
    const bytes = new Uint8Array(buffer);
    for (let i = 0; i < bytes.byteLength; i++) {
        binary += String.fromCharCode(bytes[i]);
    }
    return window.btoa(binary);
}

// 将 Base64 字符串转换为 ArrayBuffer
function base64ToArrayBuffer(base64) {
    const binary = window.atob(base64);
    const bytes = new Uint8Array(binary.length);
    for (let i = 0; i < binary.length; i++) {
        bytes[i] = binary.charCodeAt(i);
    }
    return bytes.buffer;
}

// 处理 FIDO2 注册选项
function processRegistrationOptions(options) {
    if (options.challenge) {
        options.challenge = new Uint8Array(options.challenge);
    }
    if (options.user && options.user.id) {
        options.user.id = new Uint8Array(options.user.id);
    }
    return options;
}

// 处理 FIDO2 认证选项
function processAuthenticationOptions(options) {
    if (options.challenge) {
        options.challenge = new Uint8Array(options.challenge);
    }
    if (options.allowCredentials) {
        options.allowCredentials = options.allowCredentials.map(cred => ({
            ...cred,
            id: new Uint8Array(cred.id)
        }));
    }
    return options;
}

// 将凭证转换为可序列化的格式
function credentialToJSON(credential) {
    return {
        id: arrayBufferToBase64(credential.rawId),
        rawId: Array.from(new Uint8Array(credential.rawId)),
        response: {
            clientDataJSON: Array.from(new Uint8Array(credential.response.clientDataJSON)),
            attestationObject: credential.response.attestationObject ? 
                Array.from(new Uint8Array(credential.response.attestationObject)) : undefined,
            authenticatorData: credential.response.authenticatorData ?
                Array.from(new Uint8Array(credential.response.authenticatorData)) : undefined,
            signature: credential.response.signature ?
                Array.from(new Uint8Array(credential.response.signature)) : undefined
        },
        type: credential.type
    };
}

// 显示错误信息
function showError(message) {
    const statusDiv = document.getElementById('status');
    if (statusDiv) {
        statusDiv.innerHTML = '<div class="error">❌ 错误: ' + message + '</div>';
    } else {
        alert('错误: ' + message);
    }
}

// 显示成功信息
function showSuccess(message) {
    const statusDiv = document.getElementById('status');
    if (statusDiv) {
        statusDiv.innerHTML = '<div class="success">✅ ' + message + '</div>';
    }
}

// 显示加载信息
function showLoading(message) {
    const statusDiv = document.getElementById('status');
    if (statusDiv) {
        statusDiv.innerHTML = '<div class="loading">⏳ ' + message + '</div>';
    }
}

// 检查浏览器兼容性
document.addEventListener('DOMContentLoaded', function() {
    if (!isFido2Supported()) {
        console.warn('此浏览器不支持 WebAuthn/FIDO2');
    }
});

