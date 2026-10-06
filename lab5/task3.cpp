#include <iostream>
#include <string>
using namespace std;

struct Coach {
    int number;
    string type;
    int capacity;
    int currentPassengers;
    Coach* next;
    Coach* prev;
};

class Train {
private:
    Coach* current;
    int totalCoaches;

public:
    Train() {
        current = NULL;
        totalCoaches = 0;
    }

    // 1. Add Coach at the end
    void addCoach(int number, string type, int capacity, int currentPassengers) {
        Coach* newCoach = new Coach{number, type, capacity, currentPassengers, NULL, NULL};

        if (current == NULL) {
            newCoach->next = newCoach;
            newCoach->prev = newCoach;
            current = newCoach;
        } else {
            Coach* last = current->prev;
            last->next = newCoach;
            newCoach->prev = last;
            newCoach->next = current;
            current->prev = newCoach;
        }
        totalCoaches++;
        cout << "Coach " << number << " added.\n";
    }

    // 2. Insert Coach after a given coach number
    void insertCoach(int afterNumber, int number, string type, int capacity, int currentPassengers) {
        if (current == NULL) {
            addCoach(number, type, capacity, currentPassengers);
            return;
        }

        Coach* temp = current;
        do {
            if (temp->number == afterNumber) {
                Coach* newCoach = new Coach{number, type, capacity, currentPassengers, NULL, NULL};

                newCoach->next = temp->next;
                newCoach->prev = temp;
                temp->next->prev = newCoach;
                temp->next = newCoach;

                totalCoaches++;
                cout << "Coach " << number << " inserted after " << afterNumber << ".\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "Coach " << afterNumber << " not found.\n";
    }

    // 3. Remove Coach by number
    void removeCoach(int number) {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        Coach* temp = current;
        do {
            if (temp->number == number) {
                if (temp->next == temp) {          // only one coach
                    delete temp;
                    current = NULL;
                    totalCoaches = 0;
                    cout << "Coach " << number << " removed. Train is empty.\n";
                    return;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                if (temp == current)
                    current = temp->next;

                delete temp;
                totalCoaches--;
                cout << "Coach " << number << " removed.\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "Coach " << number << " not found.\n";
    }

    // 4. Move Forward
    void moveForward() {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }
        current = current->next;
        cout << "Moved to next coach.\n";
    }

    // 5. Move Backward
    void moveBackward() {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }
        current = current->prev;
        cout << "Moved to previous coach.\n";
    }

    // 6. Display Clockwise (Forward)
    void displayClockwise() {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        cout << "\n===== Train (Clockwise) =====\n";
        Coach* temp = current;
        do {
            cout << "Coach " << temp->number 
                 << " | Type: " << temp->type
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->currentPassengers << endl;
            temp = temp->next;
        } while (temp != current);
        cout << "=============================\n";
    }

    // 7. Display Anti-clockwise (Backward)
    void displayAntiClockwise() {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        cout << "\n===== Train (Anti-clockwise) =====\n";
        Coach* temp = current;
        do {
            cout << "Coach " << temp->number 
                 << " | Type: " << temp->type
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->currentPassengers << endl;
            temp = temp->prev;
        } while (temp != current);
        cout << "==================================\n";
    }

    // 8. Search Coach
    void searchCoach(int number) {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        Coach* temp = current;
        do {
            if (temp->number == number) {
                cout << "\n===== Coach Found =====\n";
                cout << "Number     : " << temp->number << endl;
                cout << "Type       : " << temp->type << endl;
                cout << "Capacity   : " << temp->capacity << endl;
                cout << "Passengers : " << temp->currentPassengers << endl;
                cout << "Empty Seats: " << (temp->capacity - temp->currentPassengers) << endl;
                cout << "=======================\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "Coach " << number << " not found.\n";
    }

    // 9. Find Maximum Available Capacity (most empty seats)
    void findMaxAvailable() {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        Coach* temp = current;
        Coach* maxCoach = current;
        int maxEmpty = current->capacity - current->currentPassengers;

        do {
            int empty = temp->capacity - temp->currentPassengers;
            if (empty > maxEmpty) {
                maxEmpty = empty;
                maxCoach = temp;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "\n===== Coach with Maximum Empty Seats =====\n";
        cout << "Coach Number : " << maxCoach->number << endl;
        cout << "Type         : " << maxCoach->type << endl;
        cout << "Empty Seats  : " << maxEmpty << endl;
        cout << "==========================================\n";
    }

    // 10. Display Current Coach
    void displayCurrent() {
        if (current == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        cout << "\n===== Current Coach =====\n";
        cout << "Number     : " << current->number << endl;
        cout << "Type       : " << current->type << endl;
        cout << "Capacity   : " << current->capacity << endl;
        cout << "Passengers : " << current->currentPassengers << endl;
        cout << "Empty Seats: " << (current->capacity - current->currentPassengers) << endl;
        cout << "=========================\n";
    }

    // 11. Reverse Train Direction (Important)
    void reverseTrain() {
        if (current == NULL || current->next == current) {
            cout << "Nothing to reverse.\n";
            return;
        }

        Coach* curr = current;
        Coach* temp = NULL;

        // Swap next and prev of every node
        do {
            temp = curr->next;
            curr->next = curr->prev;
            curr->prev = temp;
            curr = curr->prev;          // move using new prev
        } while (curr != current);

        // Update current (optional but recommended)
        // After swap, the old next becomes prev, so we can keep current same
        // or move it if required. Here we keep it.

        cout << "Train direction reversed successfully.\n";
    }
};

// ==================== MENU ====================
int main() {
    Train train;
    int choice, n, number, capacity, passengers, afterNumber;
    string type;

    cout << "Enter number of coaches: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nCoach " << i + 1 << " details:\n";
        cout << "Coach Number: ";
        cin >> number;
        cin.ignore();
        cout << "Type: ";
        getline(cin, type);
        cout << "Capacity: ";
        cin >> capacity;
        cout << "Current Passengers: ";
        cin >> passengers;
        train.addCoach(number, type, capacity, passengers);
    }

    do {
        cout << "\n========= Train Coach Manager =========\n";
        cout << "1.  Add Coach\n";
        cout << "2.  Insert Coach after a number\n";
        cout << "3.  Remove Coach\n";
        cout << "4.  Move Forward\n";
        cout << "5.  Move Backward\n";
        cout << "6.  Display Clockwise\n";
        cout << "7.  Display Anti-clockwise\n";
        cout << "8.  Search Coach\n";
        cout << "9.  Find Max Available Capacity\n";
        cout << "10. Display Current Coach\n";
        cout << "11. Reverse Train Direction\n";
        cout << "0.  Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Number: "; cin >> number; cin.ignore();
                cout << "Type: "; getline(cin, type);
                cout << "Capacity: "; cin >> capacity;
                cout << "Passengers: "; cin >> passengers;
                train.addCoach(number, type, capacity, passengers);
                break;
            case 2:
                cout << "Insert after Coach Number: "; cin >> afterNumber;
                cout << "New Coach Number: "; cin >> number; cin.ignore();
                cout << "Type: "; getline(cin, type);
                cout << "Capacity: "; cin >> capacity;
                cout << "Passengers: "; cin >> passengers;
                train.insertCoach(afterNumber, number, type, capacity, passengers);
                break;
            case 3:
                cout << "Enter Coach Number to remove: ";
                cin >> number;
                train.removeCoach(number);
                break;
            case 4: train.moveForward(); break;
            case 5: train.moveBackward(); break;
            case 6: train.displayClockwise(); break;
            case 7: train.displayAntiClockwise(); break;
            case 8:
                cout << "Enter Coach Number: ";
                cin >> number;
                train.searchCoach(number);
                break;
            case 9: train.findMaxAvailable(); break;
            case 10: train.displayCurrent(); break;
            case 11: train.reverseTrain(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}