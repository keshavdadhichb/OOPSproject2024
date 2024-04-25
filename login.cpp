#include <iostream>
#include <string>
#include <regex>

using namespace std;

bool isValidEmail(const string& email) 
{
    regex pattern("(\\w+)(\\.\\w+)*@(vitstudent\\.ac\\.in)");
    return regex_match(email, pattern);
}

int main() 
{
    string email, roomNumber;

    cout << "Enter your email (must end with @vitstudent.ac.in): ";
    cin >> email;

    if (!isValidEmail(email))
     {
        cout << "Invalid email format. Please enter a valid VIT student email address." << endl;
        return 1;
    }

    cout << "Enter your room number: ";
    cin >> roomNumber;

    cout << "\nLogin successful!" << endl;
    cout << "Email: " << email << endl;
    cout << "Room Number: " << roomNumber << endl;

    return 0;
}
