import requests
from tabulate import tabulate

url = "http://3.12.155.102:3001/"  

print("***************************\n" \
    "***************************\n" \
    "*******Welcome to the******\n" \
    "*******LED interface*******\n" \
    "***************************\n" \
    "***************************\n\n\n" )

start = input("Enter ! to get started: ")

if start == "!":

    print("\n*To terminate a process enter exit")

    while True:
        choice = input(
        
        
        "__________________________\n"
        "|1) To create an account |\n"\
        "|                        |\n"\
        "|2) To login             |\n" \
        "|                        |\n"
        "|3) Display all users    |\n"
        "|                        |\n"
        "|4) Delete User          |\n"
        "|________________________|\n" \
        "\n" \
        "Enter your choice: "
        )
        if(choice == "1"):
            while True:
                email = input("Enter the email you want to use: ")
                if email == "exit":
                    break
                email = email.upper()
                Passw = input("Enter the password you want to use: ")
                if Passw == "exit":
                    break
                id = input("Enter the mac acdress of youe esp: ")
                if id == "exit":
                    break
                response = requests.put(url + "newacc/" + email + "/" + Passw + "/" + id)
                if response.text == "bad":
                    print("Email already in use")
                    break
                else:
                    print("Account created")
                    break
        elif(choice == "2"):
            while True:
                email = input("Enter your email: ")
                if email == "exit":
                    break
                password = input("Enter your password: ")
                if password == "exit":
                    break
                email = email.upper()
                response = requests.get(url + "verify/" + email + "/" + password)
                x = response.text
                if x == "failed":
                    print("Username or Password was incorrect")
                    
                else:
                    while True:
                        choise = input(
                            "__________________________\n"
                            "|1) Enter Message        |\n"\
                            "|                        |\n"
                            "|2) Clear Board          |\n"
                            "|                        |\n"\
                            "|3) Log Out              |\n"\
                            "|________________________|\n"\
                            "\n"\
                            "Enter your choice: "
                            )
                        if(choise == "1"):
                            v = input(
                            "__________________________\n"
                            "|1) Enter custom message |\n"\
                            "|                        |\n"
                            "|2) Choose from preset   |\n"
                            "|                        |\n"\
                            "|3) Edit presets         |\n"\
                            "|________________________|\n"\
                            "\n"\
                            "Enter your choice: "
                            )
                            if(v == "1"):
                                message = input("Enter your message: ")
                                while True:
                                    color = input( "__________________________\n"
                                                "|1) Red                  |\n"\
                                                "|                        |\n"
                                                "|2) Green                |\n"
                                                "|                        |\n"\
                                                "|3) Blue                 |\n"\
                                                "|                        |\n"\
                                                "|4) White                |\n"\
                                                "|                        |\n"\
                                                "|5) Pink                 |\n"
                                                "|                        |\n"\
                                                "|6) Yellow               |\n"
                                                "|________________________|\n"\
                                                "\n"\
                                                "Enter your color: ")
                                    if color == "1" or color == "2" or color == "3" or color == "4" or color == "5" or color == "6":
                                        break
                                    elif color == "exit":
                                        break
                                    print("please enter a valid choice")
                                response = requests.put(url + "setmes/" + message + "/" + color + "/" + email)
                                print(response.text)
                            elif(v == "2"): 

                                while True:
                                    response = requests.get(url + "getpre/" + email)
                                    x = 1
                                    arr = []
                                    my_dict = response.json()[0]
                                    for value in my_dict.values():
                                        arr.append(value)
                                        print(str(x) + ") " + value + "\n")
                                        x += 1
                                    pre = input ("Enter the preset you want to use: ")
                                    print("\n")
                                    if pre == "exit":
                                        break
                                    if int(pre) > len(my_dict) or int(pre) < 1:
                                        print("Please enter a valid choice")
                                        print("\n")
                                    else:
                                        break
                                while True:   
                                    if pre == "exit": 
                                        break
                                    color = input( "__________________________\n"
                                                "|1) Red                  |\n"\
                                                "|                        |\n"
                                                "|2) Green                |\n"
                                                "|                        |\n"\
                                                "|3) Blue                 |\n"\
                                                "|                        |\n"\
                                                "|4) White                |\n"\
                                                "|                        |\n"\
                                                "|5) Pink                 |\n"
                                                "|                        |\n"\
                                                "|6) Yellow               |\n"
                                                "|________________________|\n"\
                                                "\n"\
                                                "Enter your color: ")
                                    if int(color) >= 1 or int(color) <= 6:
                                        response = requests.put(url + "setmes/" + arr[int(pre)-1] + "/" + color + "/" + email)
                                        print(response.text)
                                        break
                                    elif color == "exit":
                                        break
                                    print("please enter a valid choice")
                            elif(v == "3"):
                                while True:
                                    response = requests.get(url + "getpre/" + email)
                                    x = 1
                                    my_dict = response.json()[0]
                                    for value in my_dict.values():
                                        print(str(x) + ") " + value + "\n")
                                        x += 1
                                    pre = input ("Enter the preset you want to change, to add a preset enter " + (str(len(my_dict) + 1)) + ": ")
                                    print("\n")
                                    if pre == "exit":
                                        break
                                    if int(pre) > len(my_dict) + 1 or int(pre) < 1:
                                        print("Please enter a valid choice")
                                        print("\n")
                                    else:
                                        break
                                while True:
                                    if pre == "exit":
                                        break
                                    mes = input("Enter the message you want to add: ")
                                    response = requests.put(url + "edit_pre/" + mes + "/" + pre + "/" + email)
                                    print(response.text)
                                    if True:
                                        break
                                    
                                    
                                    


                        elif(choise == "2"):
                            response = requests.put(url + "clear/" + email)
                            print("cleared")
                        elif(choise == "3"):
                            break
                    break
        elif(choice == "3"):
            print("\n")
            response = requests.get(url + "getall" )
            data = response.json()
            headers = ["Index"] + list(data[0].keys())  
            rows = [[i] + list(item.values()) for i, item in enumerate(data, start=1)] 
            print(tabulate(rows, headers=headers, tablefmt="psql"))

            
        elif(choice == "4"):
            while True:
                mail = input("Type the email of the user you would like to delete: ")
                if(mail == "exit"):
                    break
                mail = mail.upper()
                response = requests.put(url + "delete/" + mail)
                print(response.text)
                if(True):
                    break

            


                        
