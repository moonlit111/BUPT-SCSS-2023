user_name = "lhl2004"
pwd = "1234567"

while True:
    username_input = input("please input username: ")

    if(username_input == user_name):
        while True:
            pwd_input = input("please input password: ")
            if (pwd_input == pwd):
                print("Congratulation! You have passed the verification!\n")
                break
            else:
                print("incorrect password!\n")
        break
    else:
        print("incorrect username!\n")
