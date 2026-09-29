#include <iostream>
#include <vector>
using namespace std;

struct Person {
    int id;
    Person* next;
    Person(int i) { id = i; next = nullptr; }
};

// Create Circle: 1 -> 2 -> ... -> N -> again 1
Person* createCircle(int n) {
    Person* head = new Person(1);
    Person* last = head;
    for (int i = 2; i <= n; i++) {
        last->next = new Person(i);
        last = last->next;
    }
    last->next = head;              
    return head;
}

int main() {
    int n, k;
    cout << "Number of people (N): "; cin >> n;
    cout << "Step count (k): ";       cin >> k;
    if (n < 1 || k < 1) { cout << "N and k must be >= 1\n"; return 0; }

    Person* head = createCircle(n);

  
    Person* prev = head;
    while (prev->next != head) prev = prev->next;   
    Person* cur = head;                             

    vector<int> eliminated;

 
    while (cur->next != cur) {
        for (int i = 1; i < k; i++) {              
            prev = cur;
            cur = cur->next;
        }
        eliminated.push_back(cur->id);              
        prev->next = cur->next;                  
        delete cur;
        cur = prev->next;                            
    }

    cout << "\nEliminated order: ";
    for (int id : eliminated) cout << id << " ";
    cout << "\nSurvivor: " << cur->id << endl;

    delete cur;                                 
    return 0;
}