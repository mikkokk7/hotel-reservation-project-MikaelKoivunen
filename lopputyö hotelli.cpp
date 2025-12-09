// Mikael Koivunen 25TietoB

#include <iostream>   // basic input/output
#include <string>     // for string and getline
#include <cstdlib>    // for rand, srand
#include <ctime>      // for time seed

using namespace std;

const int MAX_ROOMS = 300;  // maximum size of the room arrays

// Simple struct that stores one reservation
struct Reservation {
    int reservationNumber;
    string name;
    int roomNumber;
    int nights;
    int pricePerNight;
};

// Random number helper function
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Checks if a room is free or not.
// Returns true if room exists and is not reserved.
bool isRoomFree(bool reserved[], int roomCount, int roomNumber) {
    int index = roomNumber - 1;

    // invalid room number
    if (index < 0 || index >= roomCount) {
        return false;
    }

    return !reserved[index]; // free if reserved[index] is false
}

// Reads an integer from user with simple error checking
int readInt(const string& message) {
    int value;
    cout << message;
    while (!(cin >> value)) {
        cout << "Invalid input, please enter a number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n'); // clear leftover characters
    return value;
}

// Creates a new reservation and stores it in arrays
void makeReservation(bool reserved[],
    Reservation reservations[],
    int roomCount,
    int pricePerNight) {

    // Check if there is at least one free room
    bool freeRoomExists = false;
    for (int i = 0; i < roomCount; i++) {
        if (!reserved[i]) {
            freeRoomExists = true;
            break;
        }
    }

    if (!freeRoomExists) {
        cout << "All rooms are already reserved.\n\n";
        return;
    }

    // Read customer name (getline required by assignment)
    cout << "Enter customer name: ";
    string customerName;
    getline(cin, customerName);

    // Read number of nights (must be at least 1)
    int nights = 0;
    while (nights < 1) {
        nights = readInt("Enter number of nights (>= 1): ");
        if (nights < 1) {
            cout << "Nights must be at least 1.\n";
        }
    }

    // Pick a random free room
    int roomNumber;
    do {
        roomNumber = randomInRange(1, roomCount);
    } while (!isRoomFree(reserved, roomCount, roomNumber));

    // Generate a reservation number
    int reservationNumber = randomInRange(10000, 99999);

    int index = roomNumber - 1;
    reserved[index] = true;

    // Store reservation data
    reservations[index].reservationNumber = reservationNumber;
    reservations[index].name = customerName;
    reservations[index].roomNumber = roomNumber;
    reservations[index].nights = nights;
    reservations[index].pricePerNight = pricePerNight;

    int totalCost = nights * pricePerNight;

    cout << "\nReservation created successfully.\n";
    cout << "Reservation number: " << reservationNumber << "\n";
    cout << "Room number: " << roomNumber << "\n";
    cout << "Price per night: " << pricePerNight << " EUR\n";
    cout << "Total price: " << totalCost << " EUR\n\n";
}

// Search reservation by reservation number
void searchByNumber(bool reserved[],
    Reservation reservations[],
    int roomCount) {

    int number = readInt("Enter reservation number: ");

    bool found = false;

    // Loop through all rooms
    for (int i = 0; i < roomCount; i++) {
        if (reserved[i] && reservations[i].reservationNumber == number) {
            cout << "\nReservation found:\n";
            cout << "Name: " << reservations[i].name << "\n";
            cout << "Room: " << reservations[i].roomNumber << "\n";
            cout << "Nights: " << reservations[i].nights << "\n";
            cout << "Total: "
                << reservations[i].nights * reservations[i].pricePerNight
                << " EUR\n\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No reservation found with that number.\n\n";
    }
}

// Search reservations by name (partial match allowed)
void searchByName(bool reserved[],
    Reservation reservations[],
    int roomCount) {

    cout << "Enter name (or part of name): ";
    string part;
    getline(cin, part);

    bool found = false;

    for (int i = 0; i < roomCount; i++) {
        if (reserved[i]) {
            // Check if substring exists
            if (reservations[i].name.find(part) != string::npos) {
                if (!found) {
                    cout << "\nMatching reservations:\n";
                }
                found = true;
                cout << "----------------------\n";
                cout << "Reservation number: " << reservations[i].reservationNumber << "\n";
                cout << "Name: " << reservations[i].name << "\n";
                cout << "Room: " << reservations[i].roomNumber << "\n";
                cout << "Nights: " << reservations[i].nights << "\n";
                cout << "Total: "
                    << reservations[i].nights * reservations[i].pricePerNight
                    << " EUR\n";
            }
        }
    }

    if (!found) {
        cout << "No reservations found for that name.\n";
    }
    cout << "\n";
}

// Prints all reservations 
void printAllReservations(bool reserved[],
    Reservation reservations[],
    int roomCount) {

    bool any = false;

    for (int i = 0; i < roomCount; i++) {
        if (reserved[i]) {
            if (!any) {
                cout << "All reservations:\n";
            }
            any = true;
            cout << "----------------------\n";
            cout << "Reservation number: " << reservations[i].reservationNumber << "\n";
            cout << "Name: " << reservations[i].name << "\n";
            cout << "Room: " << reservations[i].roomNumber << "\n";
            cout << "Nights: " << reservations[i].nights << "\n";
            cout << "Total: "
                << reservations[i].nights * reservations[i].pricePerNight
                << " EUR\n";
        }
    }

    if (!any) {
        cout << "No reservations have been made yet.\n";
    }
    cout << "\n";
}

int main() {
    srand((unsigned int)time(0)); // seed for random numbers

    // Random number of rooms between 30 and 70
    int roomCount = randomInRange(30, 70);

    // Random price between 80 and 100
    int pricePerNight = randomInRange(80, 100);

    // room arrays
    bool reserved[MAX_ROOMS];
    Reservation reservations[MAX_ROOMS];

    // initialize all rooms as free
    for (int i = 0; i < roomCount; i++) {
        reserved[i] = false;
    }

    cout << "Welcome to the hotel reservation system!\n";
    cout << "Total rooms: " << roomCount << "\n";
    cout << "Price per night: " << pricePerNight << " EUR\n\n";

    int choice;

    // Simple main menu loop
    do {
        cout << "MENU\n";
        cout << "1) Make new reservation\n";
        cout << "2) Search by reservation number\n";
        cout << "3) Search by name\n";
        cout << "4) Show all reservations\n";
        cout << "0) Quit\n";

        choice = readInt("Your choice: ");

        if (choice == 1) {
            makeReservation(reserved, reservations, roomCount, pricePerNight);
        }
        else if (choice == 2) {
            searchByNumber(reserved, reservations, roomCount);
        }
        else if (choice == 3) {
            searchByName(reserved, reservations, roomCount);
        }
        else if (choice == 4) {
            printAllReservations(reserved, reservations, roomCount);
        }
        else if (choice == 0) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid option.\n\n";
        }

    } while (choice != 0);

    return 0;
}
