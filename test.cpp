#include <iostream>

using namespace std;

int main() {
    string name;
    string option;
    cout << "hello" << endl;
    cin >> option;
    while (getline(cin, name)) {
        cout << "hello " << name << endl;
    }
    cin >> option;
    cout << option;
    return 0;
}