#include<iostream>
#include<string>
using namespace std;

template <typename T>
class Stack{
    T arr[1000];
    int top;
public:
    Stack() {top=-1;}
    bool isEmpty(){return top==-1;}
    void push (T x){arr[++top]=x;}
    T pop(){ return arr[top--];}
    T peek(){return arr[top];}
};

// ---------- HELPERS ----------
int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
string reverseStr(string s) {
    string r = "";
    for (int i = (int)s.length() - 1; i >= 0; i--) 
    r += s[i];
    return r;
}
double power(double a, double b) {           // simple integer power
    double res = 1;
    for (int i = 0; i < (int)b; i++) res *= a;
    return res;
}
double applyOp(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return power(a, b);                     
}
string convert(string expr,bool forPrefix){
    Stack<char> st;                         
    string result = "";
    for (int i = 0; i < (int)expr.length(); i++) {
        char ch = expr[i];
        if (ch == ' ') continue;

        if (isOperand(ch)) {
            result += ch;
        }
        else if (ch == '(') {
            st.push(ch);
        }
        else if (ch == ')') {
            while (!st.isEmpty() && st.peek() != '(')
                result += st.pop();
            if (!st.isEmpty()) st.pop();     
        }
        else if (isOperator(ch)) {
            while (!st.isEmpty() && st.peek() != '(') {
                int p1 = prec(st.peek()), p2 = prec(ch);
                bool popIt;
                if (forPrefix) popIt = (p1 > p2) || (p1 == p2 && ch == '^');
                else           popIt = (p1 > p2) || (p1 == p2 && ch != '^');
                if (!popIt) break;
                result += st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.isEmpty()) result += st.pop();
    return result;
}

// 1.
string infix_to_postfix(string expr) {
    return convert(expr, false);
}

// 2. reverse -> brackets swap -> postfix -> reverse
string infix_to_prefix(string expr) {
    string rev = reverseStr(expr);
    for (int i = 0; i < (int)rev.length(); i++) {
        if (rev[i] == '(') rev[i] = ')';
        else if (rev[i] == ')') rev[i] = '(';
    }
    string post = convert(rev, true);
    return reverseStr(post);
}

// 3.
string postfix_to_infix(string expr) {
    Stack<string> st;                        // sub-expressions ka stack
    for (int i = 0; i < (int)expr.length(); i++) {
        char ch = expr[i];
        if (ch == ' ') continue;
        if (isOperand(ch)) {
            st.push(string(1, ch));          // char -> string
        } else if (isOperator(ch)) {
            string b = st.pop();
            string a = st.pop();
            st.push("(" + a + ch + b + ")");
        }
    }
    return st.pop();
}

// 4.
double evaluate_postfix(string expr) {
    Stack<double> st;                      
    for (int i = 0; i < (int)expr.length(); i++) {
        char ch = expr[i];
        if (ch == ' ') continue;
        if (ch >= '0' && ch <= '9') {
            st.push(ch - '0');               // '5' -> 5
        } else if (isOperator(ch)) {
            double b = st.pop();            
            double a = st.pop();
            st.push(applyOp(a, b, ch));
        }
    }
    return st.pop();
}

// 5. right to left scan
double evaluate_prefix(string expr) {
    Stack<double> st;
    for (int i = (int)expr.length() - 1; i >= 0; i--) {
        char ch = expr[i];
        if (ch == ' ') continue;
        if (ch >= '0' && ch <= '9') {
            st.push(ch - '0');
        } else if (isOperator(ch)) {
            double a = st.pop();           
            double b = st.pop();
            st.push(applyOp(a, b, ch));
        }
    }
    return st.pop();
}

// ---------- MAIN ----------
int main() {
    cout << infix_to_postfix("A+B*C") << endl;       // ABC*+
    cout << infix_to_postfix("(A+B)*C") << endl;     // AB+C*
    cout << infix_to_prefix("A+B*C") << endl;        // +A*BC
    cout << infix_to_prefix("(A+B)*C") << endl;      // *+ABC
    cout << postfix_to_infix("ABC*+") << endl;       // (A+(B*C))
    cout << evaluate_postfix("231*+9-") << endl;     // -4
    cout << evaluate_prefix("-+2*319") << endl;      // -4
}
