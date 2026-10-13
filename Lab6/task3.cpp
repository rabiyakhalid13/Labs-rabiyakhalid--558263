#include <iostream>
using namespace std;

// ---------- A single print request ----------
struct Request {
    int id;
    int arrival;      // time at which the request arrived
    int processing;   // time needed to print it
};

// ---------- CIRCULAR QUEUE (dynamic resizing) ----------
class CircularQueue {
    Request* arr;
    int capacity, frontIdx, rear, count;
    static const int MIN_CAP = 4;      // never shrink below this

public:
    CircularQueue(int cap = MIN_CAP) {
        capacity = cap;
        arr = new Request[capacity];
        frontIdx = 0;                  // index of the first element
        rear = 0;                      // index of the next free slot
        count = 0;                     // number of elements stored
    }
    ~CircularQueue() { delete[] arr; } // free the dynamic memory

    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == capacity; }

    // Copy all elements into a new array of size newCap
    void resize(int newCap) {
        if (newCap < MIN_CAP || newCap < count) return;  // invalid size, ignore
        Request* newArr = new Request[newCap];
        for (int i = 0; i < count; i++)
            newArr[i] = arr[(frontIdx + i) % capacity];  // copy in queue order
        delete[] arr;
        arr = newArr;
        capacity = newCap;
        frontIdx = 0;                  // front restarts at index 0
        rear = count % newCap;         // next free slot after the last element
        cout << "   >> Resized to capacity " << newCap << endl;
    }

    void enqueue(Request x) {
        if (isFull()) resize(capacity * 2);   // full: double the capacity
        arr[rear] = x;
        rear = (rear + 1) % capacity;         // wrap around at the end
        count++;
    }

    Request dequeue() {
        if (isEmpty()) return Request{-1, 0, 0};  // empty: return a dummy request
        Request x = arr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;     // move front forward (wrap around)
        count--;
        // too sparse (<= 25% used): halve the capacity, but not below MIN_CAP
        if (capacity / 2 >= MIN_CAP && count <= capacity / 4)
            resize(capacity / 2);
        return x;
    }

    Request front() {
        if (isEmpty()) return Request{-1, 0, 0};
        return arr[frontIdx];                     // peek without removing
    }

    // Print the queue from front to back
    void display() {
        cout << "   Queue [size=" << count << ", cap=" << capacity << "]: ";
        if (isEmpty()) cout << "(empty)";
        for (int i = 0; i < count; i++) {
            Request r = arr[(frontIdx + i) % capacity];
            cout << "R" << r.id << " ";
        }
        cout << endl;
    }
};

// ---------- SIMULATION ----------
int currentTime = 0;   // time at which the printer becomes free
int totalWait = 0;     // sum of waiting times of all processed requests
int processed = 0;     // number of processed requests

// Take the front request and "print" it
void processNext(CircularQueue& q) {
    if (q.isEmpty()) return;
    Request r = q.dequeue();
    // printing starts when the printer is free AND the request has arrived
    int start = (currentTime > r.arrival) ? currentTime : r.arrival;
    int wait = start - r.arrival;              // waiting time of this request
    currentTime = start + r.processing;        // printer is busy until this time
    totalWait += wait;
    processed++;
    cout << "Dequeue R" << r.id << " (wait=" << wait << ")" << endl;
    q.display();
}

// Add a new request and show the queue state
void addRequest(CircularQueue& q, int id, int arrival, int proc) {
    cout << "Enqueue R" << id << endl;
    q.enqueue(Request{id, arrival, proc});
    q.display();
}

int main() {
    CircularQueue q;                           // starts with capacity 4

    addRequest(q, 1, 0, 5);
    addRequest(q, 2, 1, 3);
    addRequest(q, 3, 2, 4);
    addRequest(q, 4, 3, 2);
    addRequest(q, 5, 4, 6);                    // queue was full -> resize up

    processNext(q);
    processNext(q);
    processNext(q);                            // queue becomes sparse -> resize down

    addRequest(q, 6, 6, 2);
    addRequest(q, 7, 7, 1);
    addRequest(q, 8, 8, 3);                    // full again -> resize up

    while (!q.isEmpty()) processNext(q);       // process everything that is left

    cout << "\nProcessed: " << processed << endl;
    cout << "Average waiting time: " << (double)totalWait / processed << endl;
}