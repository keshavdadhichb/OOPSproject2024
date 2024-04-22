#include <iostream>
#include <iomanip>

using namespace std;

void displayTimeSlots() {
    cout << "Available Time Slots for Room Cleaning:" << endl;
    int hour = 10;
    int minute = 0;

    while (hour <= 19) {
        cout << setw(2) << (hour < 10 ? "0" : "") << hour << ":" << (minute == 0 ? "00" : "30") << endl;
        minute += 30;
        if (minute == 60) {
            minute = 0;
            hour++;
        }
    }
}

int main() {
    displayTimeSlots();

    int choice;
    cout << "\nEnter the slot number you want to book: ";
    cin >> choice;

    if (choice < 1 || choice > 24) {
        cout << "Invalid choice. Please select a valid slot." << endl;
        return 1;
    }

    cout << "\nYou have successfully booked the slot at ";
    if (choice <= 9) {
        cout << "0";
    }
    cout << choice << ":00 for room cleaning." << endl;

    return 0;
}
