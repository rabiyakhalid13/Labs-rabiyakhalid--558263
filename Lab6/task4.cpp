#include <iostream>
using namespace std;

class WaitingRoom {
    static const int MAX = 100;   // maximum patients that can wait at once
    int arr[MAX];                 // stores the IDs of waiting patients
    int frontIdx;                 // index of the patient who will be served next
    int rear;                     // index of the next free slot
    int count;                    // number of patients currently waiting
    int nextId;                   // next auto-generated ID (starts from 1)

public:
    WaitingRoom() {
        frontIdx = 0;
        rear = 0;
        count = 0;
        nextId = 1;
    }

    // Assign a new unique ID and add the patient at the back of the queue
    int RegisterPatient() {
        if (count == MAX) {
            cout << "Waiting room is full, cannot register." << endl;
            return -1;
        }
        int id = nextId++;            // use the ID, then increase it for the next patient
        arr[rear] = id;
        rear = (rear + 1) % MAX;      // wrap around at the end of the array
        count++;
        cout << "Registered patient with ID " << id << endl;
        return id;
    }

    // Call the patient at the front of the queue (first come, first served)
    int ServePatient() {
        if (count == 0) {
            cout << "No patient is waiting." << endl;
            return -1;
        }
        int id = arr[frontIdx];
        frontIdx = (frontIdx + 1) % MAX;   // move front forward (wrap around)
        count--;
        cout << "Serving patient with ID " << id << endl;
        return id;
    }

    // Remove all waiting patients (doctor goes to lunch)
    void CancelAll() {
        frontIdx = 0;
        rear = 0;
        count = 0;
        // nextId is NOT reset, so IDs stay unique even after cancelling
        cout << "All appointments cancelled." << endl;
    }

    // True only if nobody is waiting
    bool CanDoctorGoHome() {
        return count == 0;
    }

    // Show all waiting IDs in sorted (ascending) order
    void ShowAllPatient() {
        if (count == 0) {
            cout << "No patients waiting." << endl;
            return;
        }
        // copy the IDs in queue order into a temporary array
        int temp[MAX];
        for (int i = 0; i < count; i++)
            temp[i] = arr[(frontIdx + i) % MAX];

        // bubble sort the copy (the original queue stays untouched)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (temp[j] > temp[j + 1]) {
                    int t = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = t;
                }
            }
        }

        cout << "Waiting patients: ";
        for (int i = 0; i < count; i++)
            cout << temp[i] << " ";
        cout << endl;
    }
};

int main() {
    WaitingRoom w;

    w.RegisterPatient();   // ID 1
    w.RegisterPatient();   // ID 2
    w.RegisterPatient();   // ID 3
    w.RegisterPatient();   // ID 4
    w.RegisterPatient();   // ID 5
    w.ShowAllPatient();    // 1 2 3 4 5

    w.ServePatient();      // serves 1
    w.ServePatient();      // serves 2
    w.ShowAllPatient();    // 3 4 5

    cout << "Can doctor go home? " << (w.CanDoctorGoHome() ? "Yes" : "No") << endl;  // No

    w.CancelAll();
    cout << "Can doctor go home? " << (w.CanDoctorGoHome() ? "Yes" : "No") << endl;  // Yes

    w.RegisterPatient();   // ID 6 (IDs do not restart)
    w.ShowAllPatient();    // 6
}