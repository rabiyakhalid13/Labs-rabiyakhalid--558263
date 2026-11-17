#include <iostream>
using namespace std;

int S, T, K, M;          // S = start value, T = target, K = max operations, M = overflow bound
int n;                   // number of allowed operations
char opType[10];         // operation type: + - * /
int opVal[10];           // operation operand (the number)

/* ---------- Operation Stack ---------- */
// Stores the INDEX of each chosen operation
int stk[50];
int top = 0;
void push(int x) { stk[top] = x; top++; }
void pop()       { top--; }

// Apply operation number i to the given value and return the result
int applyOp(int value, int i) {
    if (opType[i] == '+') return value + opVal[i];
    if (opType[i] == '-') return value - opVal[i];
    if (opType[i] == '*') return value * opVal[i];
    return value / opVal[i];     // '/' (integer division)
}

int found = 0;   // number of valid sequences found so far

// Print the sequence currently stored in the stack
void printSequence() {
    found++;
    cout << "Sequence " << found << ": " << S;
    int value = S;
    for (int k = 0; k < top; k++) {
        int i = stk[k];
        value = applyOp(value, i);
        cout << " -> " << opType[i] << opVal[i] << " -> " << value;
    }
    cout << endl;
}

/* ---------- Backtracking ---------- */
void solve(int value, int used) {

    // Solution found: print it, but do NOT return,
    // because longer sequences may also reach T
    if (value == T) printSequence();

    // Operation budget exhausted: stop going deeper
    if (used == K) return;

    // Try every allowed operation
    for (int i = 0; i < n; i++) {
        int next = applyOp(value, i);

        // PRUNING: skip if the value becomes negative or exceeds the overflow bound
        if (next < 0 || next > M) continue;

        push(i);                    // MAKE: push the chosen operation
        solve(next, used + 1);      // RECURSE: continue with the new value
        pop();                      // UNDO: pop the operation (backtrack)
    }
}

int main() {
    cout << "Start S, Target T, Max ops K, Overflow M: ";
    cin >> S >> T >> K >> M;

    cout << "Number of operations: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Operation " << i + 1 << " (type number, e.g. + 3): ";
        cin >> opType[i] >> opVal[i];
    }

    solve(S, 0);

    if (found == 0) cout << "No valid sequence." << endl;
    return 0;
}