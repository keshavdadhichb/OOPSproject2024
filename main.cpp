#include<iostream>
#include <regex>
#include <cstring>

using namespace std;

void printMenu(string option, string name = "") {
    cout << endl << "************ MENU **************" << endl;
    if (option == "login") {
        cout << "1. Login" << endl;
        cout << "2. Exit Program" << endl;
    } else if (option == "main") {
        cout << "Hello, " << name << ". Welcome to room cleaning service." << endl;
        // continue here
    } else { 
        cout << "Menu not found" << endl;
    }
}

bool isValidEmail(const string& email) {
    regex pattern("(\\w+)(\\.\\w+)*@(vitstudent\\.ac\\.in)");
    return regex_match(email, pattern);
}

class User {
    string name;
    string email;
    string room_no;
public:
    User(string n = "", string e = "", string rno = "") {
        name = n;
        email = e;
        room_no = rno;
    }
    string getName() {
        return name;
    }
    string getRoomNo() {
        return room_no;
    }
};  

int main() {
    User curUser; // keeping track of cur user details using an object of the User class
    int option;
    while (true) {
        // if curUser is empty, proceed with login menu
        if (curUser.getRoomNo() == "") {
            string name, email, roomNumber;

            printMenu("login");
            cout << "Enter your option: ";
            
            do {
                cin >> option;
                if (option != 1 && option != 2)
                    cout << "Enter valid option: ";
            } while (option != 1 && option != 2);

            if (option == 2)
                break;

            cout << endl << "************ Logging in **************" << endl;
            cout << "Enter name: ";
            string temp;
            getline(cin, temp);
            getline(cin, name);
            cout << "Hello " << name << "!" << endl;

            do {
                cout << "Enter your VIT email ID: ";
                cin >> email;
                if (!isValidEmail(email))
                    cout << "Invalid email format. Please enter a valid VIT student email address." << endl;
            } while (!isValidEmail(email));

            cout << "Enter your room number: ";
            cin >> roomNumber;

            curUser = User(name, email, roomNumber);
            cout << "Successfully logged in" << endl;
        }
        // if curUser is not empty, proceed with main menu
        else {
            printMenu("main", curUser.getName());
            cin >> option;
            if (option == 1)
                curUser = User();
            // TODO: check if room cleaning is already booked for the current user's room
        }

    }
    cout << endl << "See you later!" << endl;
    return 0;
}