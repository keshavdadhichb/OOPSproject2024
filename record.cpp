#include <iostream>
#include <string>

using namespace std;

struct Clean {
    string date;
    int choice;
};

void display(Clean record[], int size) {
    cout << "\nCleaning Records:" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Date: " << record[i].date << ", Choice: " << record[i].choice << endl;
    }
}

int main() {
    const int max = 100; 
    Clean clean[max];
    int count = 0;

    cout << "Welcome to Room Cleaning Log System!" << endl;

    while (true) {
        string date;
        int choice;

        cout << "\nEnter the date (YYYY-MM-DD) or type 'exit' to finish: ";
        cin >> date;

        if (date == "exit") {
            break;
        }

        cout << "Enter the choice (1-24 for 24-hour clock): ";
        cin >> choice;

        if (choice < 1 || choice > 24) {
            cout << "Invalid choice! Please enter a number between 1 and 24." << endl;
            continue;
        }

        clean[count].date = date;
        clean[count].choice = choice;
        ++count;

        cout << "Record added successfully." << endl;
    }

    display(clean, count);

    return 0;
}
