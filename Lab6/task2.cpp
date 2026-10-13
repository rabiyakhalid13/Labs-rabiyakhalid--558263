#include <iostream>
#include <string>
#include <vector>
using namespace std;


template <typename T>
class Stack {
    T arr[1000];
    int top;
public:
    Stack() { top = -1; }
    bool isEmpty() { return top == -1; }
    void push(T x) { arr[++top] = x; }
    T pop()  { return arr[top--]; }
    T peek() { return arr[top]; }
};

// ================= PART A: BRACKETS =================
bool isMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool isValidBrackets(string s) {
    Stack<char> st;
    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);                          // opening: push
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (st.isEmpty()) return false;      
            char top = st.pop();
            if (!isMatch(top, c)) return false;  
        }
    }
    return st.isEmpty();                        
}

// ================= PART B: HTML/XML TAGS =================
pair<bool, vector<string>> validate_markup(string s) {
    Stack<string> st;
    vector<string> errors;
    int n = s.length();
    int i = 0;

    while (i < n) {
        if (s[i] != '<') { i++; continue; }      // text ignore

        int j = i + 1;
        while (j < n && s[j] != '>') j++;     
        if (j == n) {
            errors.push_back("Missing '>' for tag at position " + to_string(i));
            break;
        }

        string tag = s.substr(i + 1, j - i - 1); 
        i = j + 1;

        if (tag.empty()) {
            errors.push_back("Empty tag <>");
            continue;
        }

        if (tag[0] == '/') {                     // closing tag </b>
            string name = tag.substr(1);
            if (st.isEmpty()) {
                errors.push_back("Closing tag </" + name + "> has no opening tag");
            } else {
                string top = st.pop();
                if (top != name)
                    errors.push_back("Mismatch: expected </" + top + "> but found </" + name + ">");
            }
        }
        else if (tag[tag.length() - 1] == '/') { // self-closing <br/>
            // kuch nahi karna
        }
        else {                                   // opening tag <b>
            string name = "";
            for (int k = 0; k < (int)tag.length() && tag[k] != ' '; k++)
                name += tag[k];                  
            st.push(name);
        }
    }

    while (!st.isEmpty())
        errors.push_back("Unclosed tag <" + st.pop() + ">");

    return make_pair(errors.empty(), errors);
}

// ---------- MAIN ----------
int main() {
    // Part A
    cout << isValidBrackets("{[()]}") << endl;      // 1
    cout << isValidBrackets("{[(])}") << endl;      // 0
    cout << isValidBrackets("((") << endl;          // 0
    cout << isValidBrackets("a(b)c") << endl;       // 1

    // Part B
    string tests[] = {
        "<html><body><b>Hi</b></body></html>",      // valid
        "<div><p>Hello</div></p>",                  // mismatch
        "<div><span>",                              // unclosed
        "</div>"                                    // no opening
    };
    for (int t = 0; t < 4; t++) {
        pair<bool, vector<string>> res = validate_markup(tests[t]);
        cout << tests[t] << " -> " << (res.first ? "Valid" : "Invalid") << endl;
        for (int k = 0; k < (int)res.second.size(); k++)
            cout << "   " << res.second[k] << endl;
    }
}