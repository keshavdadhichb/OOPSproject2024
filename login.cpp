#include <iostream>
#include <string>
#include <regex>

using namespace std;

bool isValidEmail(const string& email) 
{
    regex pattern("(\\w+)(\\.\\w+)*@(vitstudent\\.ac\\.in)");
    return regex_match(email, pattern);
}

bool isValidDate(const string& date) 
{
    if (date.length() != 8)
        return false;
    for (char c : date) 
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int main() 
{
    string email, password, roomNumber;

    cout << "Enter your email (must end with @vitstudent.ac.in): ";
    cin >> email;

    if (!isValidEmail(email))
     {
        cout << "Invalid email format. Please enter a valid VIT student email address." << endl;
        return 1;
    }

    cout << "Enter your date of birth (DDMMYYYY) as password: ";
    cin >> password;

    if (!isValidDate(password))
     {
        cout << "Invalid date format. Please enter your date of birth in DDMMYYYY format." << endl;
        return 1;
    }

    cout << "Enter your room number: ";
    cin >> roomNumber;

    cout << "\nLogin successful!" << endl;
    cout << "Email: " << email << endl;
    cout << "Password: " << password << endl;
    cout << "Room Number: " << roomNumber << endl;

    return 0;
}
