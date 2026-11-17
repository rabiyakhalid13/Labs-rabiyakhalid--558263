#include <iostream>
using namespace std;

// 1. Linked List (containers) 
struct Container {
    int id;
    int weight;
    Container* next;
};

Container* head = NULL;
Container* tail = NULL;

void addContainer(int id, int w) {
    Container* n = new Container;
    n->id = id;
    n->weight = w;
    n->next = NULL;

    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
}

// 2. Queue (trucks) 
int q[20];
int qFront = 0, qRear = 0;

void enqueue(int x) { q[qRear] = x; qRear++; }
int dequeue()       { int x = q[qFront]; qFront++; return x; }

/*  3. Backtracking  */
int T;               
int remaining[20];    
int load[20][50];    
int cnt[20];         

bool solve(Container* curr, int restWeight) {

    if (curr == NULL) return true;

    // PRUNING 2: 
    int totalSpace = 0;
    for (int t = 0; t < T; t++) totalSpace += remaining[t];
    if (restWeight > totalSpace) return false;

    // try every truck
    for (int t = 0; t < T; t++) {

        // PRUNING 1:
        if (remaining[t] < curr->weight) continue;

        remaining[t] -= curr->weight;
        load[t][cnt[t]] = curr->id;
        cnt[t]++;

        // RECURSE:
        if (solve(curr->next, restWeight - curr->weight))
            return true;

        // UNDO: 
        cnt[t]--;
        remaining[t] += curr->weight;
    }

    return false;   
}

/* ---------- 4. main ---------- */
int main() {
    int W, C;
    cout << "Truck capacity W: ";
    cin >> W;
    cout << "Number of trucks: ";
    cin >> T;
    cout << "Number of containers: ";
    cin >> C;


    for (int i = 0; i < T; i++) enqueue(W);


    int total = 0;
    for (int i = 0; i < C; i++) {
        int id, w;
        cout << "Container " << i + 1 << " (id weight): ";
        cin >> id >> w;
        addContainer(id, w);
        total += w;
    }


    for (int t = 0; t < T; t++) {
        remaining[t] = dequeue();
        cnt[t] = 0;
    }

    if (solve(head, total)) {
        for (int t = 0; t < T; t++) {
            cout << "Truck " << t + 1 << ": ";
            for (int k = 0; k < cnt[t]; k++)
                cout << load[t][k] << " ";
            cout << endl;
        }
    } else {
        cout << "Insufficient truck capacity." << endl;
    }
    return 0;
}