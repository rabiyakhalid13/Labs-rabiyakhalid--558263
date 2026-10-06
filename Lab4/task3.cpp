#include <iostream>
#include <string>
using namespace std;

struct BitNode {
    int bit;
    BitNode* next;
    BitNode* prev;
    BitNode(int b) { bit = b; next = nullptr; prev = nullptr; }
};

class BinaryNumber {
private:
    BitNode* head;   // MSB
    BitNode* tail;   // LSB
    int size;

    void copyFrom(const BinaryNumber& o) {
        for (BitNode* c = o.head; c != nullptr; c = c->next) appendBit(c->bit);
    }

public:
    BinaryNumber() { head = tail = nullptr; size = 0; }
    BinaryNumber(const BinaryNumber& o) { head = tail = nullptr; size = 0; copyFrom(o); }
    BinaryNumber& operator=(const BinaryNumber& o) {
        if (this != &o) { clear(); copyFrom(o); }
        return *this;
    }
    ~BinaryNumber() { clear(); }

    void clear() {
        while (head != nullptr) {
            BitNode* t = head;
            head = head->next;
            delete t;
        }
        tail = nullptr; size = 0;
    }

    void appendBit(int b) {               
        BitNode* n = new BitNode(b);
        if (tail == nullptr) head = tail = n;
        else { tail->next = n; n->prev = tail; tail = n; }
        size++;
    }

    void prependBit(int b) {                
        BitNode* n = new BitNode(b);
        if (head == nullptr) head = tail = n;
        else { n->next = head; head->prev = n; head = n; }
        size++;
    }

    void removeHead() {
        if (head == nullptr) return;
        BitNode* t = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        else tail = nullptr;
        delete t;
        size--;
    }

    void padToByte() {                    
        while (size == 0 || size % 8 != 0) prependBit(0);
    }

    void stripLeadingZeros() {
        while (size > 1 && head->bit == 0) removeHead();
    }

    // 1. Store binary number 
    bool store(const string& s) {
        clear();
        if (s.empty()) return false;
        for (char c : s) {
            if (c != '0' && c != '1') { clear(); return false; }
            appendBit(c - '0');
        }
        padToByte();
        return true;
    }

    string toString() const {
        string r = "";
        int i = 0;
        for (BitNode* c = head; c != nullptr; c = c->next, i++) {
            if (i > 0 && i % 8 == 0) r += " ";
            r += char('0' + c->bit);
        }
        return r;
    }

    // 2. 1's complement: every bit flip
    BinaryNumber onesComplement() const {
        BinaryNumber r(*this);
        for (BitNode* c = r.head; c != nullptr; c = c->next) c->bit = 1 - c->bit;
        return r;
    }

    // 4. Addition:
    static BinaryNumber add(const BinaryNumber& a, const BinaryNumber& b) {
        BinaryNumber r;
        BitNode* pa = a.tail;
        BitNode* pb = b.tail;
        int carry = 0;
        while (pa != nullptr || pb != nullptr) {
            int x = (pa != nullptr) ? pa->bit : 0;
            int y = (pb != nullptr) ? pb->bit : 0;
            int sum = x + y + carry;
            r.prependBit(sum % 2);          
            carry = sum / 2;                
            if (pa != nullptr) pa = pa->prev;
            if (pb != nullptr) pb = pb->prev;
        }
        if (carry) r.prependBit(1);
        r.padToByte();
        return r;
    }

    // 3. 2's complement = 1's complement + 1
    BinaryNumber twosComplement() const {
        BinaryNumber ones = onesComplement();
        BinaryNumber one;
        for (int i = 0; i < size - 1; i++) one.appendBit(0);
        one.appendBit(1);                   
        BinaryNumber res = add(ones, one);
        while (res.size > size) res.removeHead();   // overflow carry discard
        return res;
    }

    // 5. Multiplication: repeated addition + shifting
    static BinaryNumber multiply(const BinaryNumber& a, const BinaryNumber& b) {
        BinaryNumber result;
        result.store("0");
        BinaryNumber shifted(a);
        for (BitNode* p = b.tail; p != nullptr; p = p->prev) {   
            if (p->bit == 1) result = add(result, shifted);     
            shifted.appendBit(0);                                
        }
        result.stripLeadingZeros();
        result.padToByte();
        return result;
    }

    // 6. Decimal conversion
    unsigned long long toDecimal() const {
        unsigned long long value = 0;
        for (BitNode* c = head; c != nullptr; c = c->next)
            value = value * 2 + c->bit;
        return value;                     
    }
};

int main() {
    BinaryNumber A, B;
    string s;

    cout << "Enter binary number A: "; cin >> s;
    if (!A.store(s)) { cout << "Invalid binary!\n"; return 0; }
    cout << "Enter binary number B: "; cin >> s;
    if (!B.store(s)) { cout << "Invalid binary!\n"; return 0; }

    cout << "\nA = " << A.toString() << "\nB = " << B.toString() << endl;

    int choice;
    do {
        cout << "\n1.1's Comp(A) 2.2's Comp(A) 3.A+B 4.A*B 5.Decimal(A,B) 0.Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) cout << "1's complement: " << A.onesComplement().toString() << endl;
        else if (choice == 2) cout << "2's complement: " << A.twosComplement().toString() << endl;
        else if (choice == 3) {
            BinaryNumber r = BinaryNumber::add(A, B);
            cout << "A + B = " << r.toString() << "  (" << r.toDecimal() << ")\n";
        }
        else if (choice == 4) {
            BinaryNumber r = BinaryNumber::multiply(A, B);
            cout << "A * B = " << r.toString() << "  (" << r.toDecimal() << ")\n";
        }
        else if (choice == 5)
            cout << "A = " << A.toDecimal() << ", B = " << B.toDecimal() << endl;
    } while (choice != 0);
    return 0;
}