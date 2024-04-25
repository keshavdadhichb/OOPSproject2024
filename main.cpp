#include<iostream>
#include <regex>
#include <cstring>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

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

class Timeslots {
    map<string, int> roomToTimeslotsMap;
    bool timeslotsBooked[20] = { 0 };
public:
    bool roomAvailable(string room_no) {
        auto itr = roomToTimeslotsMap.find(room_no);
        if (itr == roomToTimeslotsMap.end()) {
            return true; // room is free
        }
        return false; // room has already booked for cleaning
    }
    
    bool addSlot(int slot, string room_no) {
        if (timeslotsBooked[slot-1] == false) {
            roomToTimeslotsMap[room_no] = slot;
            timeslotsBooked[slot-1] = true;
            return true; // successfully booked for room cleaning
        } else
        return false; // slot opted is already taken
    }
    bool slotBooked(int slot) {
        return timeslotsBooked[slot-1];
    }
};

class Cleaner {
    vector<string> feedbacks;
public:
    void addFeedback(string f) {
        feedbacks.push_back(f);
    }
    void printFeedbacks() {
        if (feedbacks.size() == 0) {
            cout << "No feedbacks" << endl;
            return;
        }
        for (const string& feedback : feedbacks) { 
            cout << feedback << endl;
        }
    }
};

void printMenu(string option, string name = "") {
    cout << endl << "************ MENU **************" << endl;
    if (option == "login") {
        cout << "1. Login" << endl;
        cout << "2. Exit Program" << endl;
    } else if (option == "main") {
        cout << "Hello, " << name << ". Welcome to room cleaning service." << endl;
       
        cout << "1. Register for room cleaning" << endl;
        cout << "2. Record completion of room cleaning" << endl;
        cout << "3. View cleaner details" << endl;
        cout << "4. Logout" << endl;
    } else { 
        cout << "Menu not found" << endl;
    }
    cout << "************ END OF MENU **************" << endl;
}

bool isValidEmail(const string& email) {
    regex pattern("(\\w+)(\\.\\w+)*@(vitstudent\\.ac\\.in)");
    return regex_match(email, pattern);
}

void displayTimeSlots(Timeslots day) {
    cout << "Available Time Slots for Room Cleaning:" << endl;
    int hour = 10;
    int minute = 0;
    int temp = 0;
    while (hour <= 19) {
        int slot = (hour-10)*2 + 1 + temp;
        // print the slot if it is free
        if (!day.slotBooked(slot))
            cout << setw(2) << "Time slot " << slot << ": " << (hour < 10 ? "0" : "") << hour << ":" << (minute == 0 ? "00" : "30") << endl;
        temp = 1 - temp;
        minute += 30;
        if (minute == 60) {
            minute = 0;
            hour++;
        }
    }
}

int main() {
    User curUser; // keeping track of cur user details using an object of the User class
    Timeslots monday, tuesday, wednesday;
    Cleaner A, B, C;
    int option;
    while (true) {
        // if curUser is empty, proceed with login menu
        if (curUser.getRoomNo() == "") {
            string name, email, roomNumber;

            printMenu("login");
            cout << "Enter your option: ";
            cin >> option;

            while (option != 1 && option != 2) {
                cout << "Enter a valid option (1 or 2): ";
                cin >> option;
            }

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
            cout << "Enter option: ";
            cin >> option;
            while (option != 1 && option != 2 && option != 3 && option != 4) {
                cout << "Enter valid option: ";
                cin >> option;
            };

            if (option == 1) { // register for room cleaning
                char day;
                cout << "Which day would you like to book for room cleaning (M, T, W): ";
                cin >> day;
                while (day != 'M' && day != 'T' && day != 'W') {
                    cout << "Enter valid day: ";
                    cin >> day;
                };

                // checking if room has already booked a slot on that day
                bool alreadyBooked = false;
                if (day == 'M') {
                    if (!monday.roomAvailable(curUser.getRoomNo())) {
                        cout << "Your room has already booked a timeslot on Monday" << endl;
                        cout << "Please book on a different slot, or register completion of cleaning if you haven\'t" << endl;
                        alreadyBooked = true;
                    }
                }
                else if (day == 'T') {
                    if (!tuesday.roomAvailable(curUser.getRoomNo())) {
                        cout << "Your room has already booked a timeslot on Tuesday" << endl;
                        cout << "Please book on a different slot, or register completion of cleaning if you haven\'t" << endl;
                        alreadyBooked = true;
                    }
                }
                else if (day == 'W') {
                    if (!wednesday.roomAvailable(curUser.getRoomNo())) {
                        cout << "Your room has already booked a timeslot on Wednesday" << endl;
                        cout << "Please book on a different slot, or register completion of cleaning if you haven\'t" << endl;
                        alreadyBooked = true;
                    }
                }

                // try booking slot
                if (!alreadyBooked) {
                    // display time slots for the selected day
                    if (day == 'M')
                        displayTimeSlots(monday);
                    else if (day == 'T')
                        displayTimeSlots(tuesday);
                    else
                        displayTimeSlots(wednesday);

                    // prompting user to choose a slot
                    int slot;
                    cout << "Enter slot number you wish to book(1-20) from above available timeslots [0 to exit]: ";
                    cin >> slot;

                    // making sure that valid slot is selected and booking the slot
                    if (!(slot == 0)) {
                        if (day == 'M') {
                            while (!monday.addSlot(slot, curUser.getRoomNo())) {
                                cout << "Slot not available. Enter a slot from the above list [Enter 0 to exit]: ";
                                cin >> slot;
                                if (slot == 0)
                                    break;
                            }
                        }
                        else if (day == 'T') {
                            while (!tuesday.addSlot(slot, curUser.getRoomNo())) {
                                cout << "Slot not available. Enter a slot from the above list [Enter 0 to exit]: ";
                                cin >> slot;
                                if (slot == 0)
                                    break;
                            }
                        }
                        else if (day == 'W') {
                            while (!wednesday.addSlot(slot, curUser.getRoomNo())) {
                                cout << "Slot not available. Enter a slot from the above list [Enter 0 to exit]: ";
                                cin >> slot;
                                if (slot == 0)
                                    break;
                            }
                        }
                    }

                    if (!(slot == 0)) {
                        cout << "Booked for room cleaning successfully!" << endl;
                        cout << "Booking details: " << endl;
                        cout << "Room no.: " << curUser.getRoomNo() << endl;
                        cout << "Day: ";
                        if (day == 'M')
                            cout << "Monday" << endl;
                        else if (day == 'T')
                            cout << "Tuesday" << endl;
                        else
                            cout << "Wednesday" << endl;
                        int hour = 10 + (slot+1)/2 - 1;
                        int minute = (slot+1)%2;
                        cout << "Slot: " << (hour < 10 ? "0" : "") << hour << ":" << (minute == 0 ? "00" : "30") << endl;
                    } else {
                        cout << "Returning to main menu" << endl;
                    }
                }
            }
            else if (option == 2) {
                cout << "Recording a room cleaning completion..." << endl;
                cout << "Enter day of cleaning (M, T, W): ";
                char day;
                cin >> day;
                while (day != 'M' && day != 'T' && day != 'W') {
                    cout << "Enter valid day: ";
                    cin >> day;
                }

                Timeslots* selectedDay;
                if (day == 'M') selectedDay = &monday;
                else if (day == 'T') selectedDay = &tuesday;
                else if (day == 'W') selectedDay = &wednesday;

                // Check if a slot was booked for the current room
                if (selectedDay->roomAvailable(curUser.getRoomNo())) {
                    cout << "No booking found for room " << curUser.getRoomNo() << " on this day." << endl;
                    cout << "Please make sure your room is booked before marking it as cleaned." << endl;
                } else {
                    cout << "Room cleaning for room " << curUser.getRoomNo() << " on ";
                    if (day == 'M') cout << "Monday";
                    else if (day == 'T') cout << "Tuesday";
                    else if (day == 'W') cout << "Wednesday";
                    cout << " marked as completed." << endl;

                    cout << "Enter cleaner name(A, B, C): ";
                    char cleanerName;
                    cin >> cleanerName;
                    while (cleanerName != 'A' && cleanerName != 'B' && cleanerName != 'C') {
                        cout << "Enter valid name: ";
                        cin >> cleanerName;
                    }

                    Cleaner* cleaner;
                    if (cleanerName == 'A') cleaner = &A;
                    else if (cleanerName == 'B') cleaner = &B;
                    else if (cleanerName == 'C') cleaner = &C;

                    // Get feedback from the user
                    cout << "Please provide your feedback about the cleaning service: ";
                    string userFeedback;
                    cin.ignore();
                    getline(cin, userFeedback);

                    cleaner->addFeedback(userFeedback);
                    cout << "Thank you for your feedback!" << endl;
                }
            }
            else if (option == 3) {
                cout << "Getting cleaner details" << endl;
                cout << "Enter cleaner name: ";
                char cleanerName;
                cin >> cleanerName;
                while (cleanerName != 'A' && cleanerName != 'B' && cleanerName != 'C') {
                        cout << "Enter valid name: ";
                    cin >> cleanerName;
                }

                Cleaner* cleaner;
                if (cleanerName == 'A') cleaner = &A;
                else if (cleanerName == 'B') cleaner = &B;
                else if (cleanerName == 'C') cleaner = &C;

                cout << "Cleaner " << cleanerName << " feedbacks: " << endl;
                cleaner->printFeedbacks();
            } else if (option == 4) {
                curUser = User();
                cout << "Successfully logged out" << endl << endl;
            }
        }
    }
    cout << endl << "See you later!" << endl;
    return 0;
}