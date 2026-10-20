#include<iostream>
#include<cctype>
#include<string>
#include<stack>
using namespace std;

struct Node{
    char data;
    Node* left;
    Node* right;
    Node(char c): data(c),left(nullptr),right(nullptr){}
};

//1.Generate a Binary Tree from the Given String
Node *buildTree(const string& s){
    stack<pair<Node*,bool>> st;
    Node* root=nullptr;
    Node* last=nullptr;

    for(char c:s){
        if(isalpha(c)){
            Node*n=new Node(c);
            if(st.empty()){
                root=n;
            }
            else if(st.top().second==false){
                st.top().first->left=n;
            }
            else{
                st.top().first->right=n;
            }
            last=n;
        }
        else if(c=='('){
            st.push({last,false});
        }
        else if(c==','){
            st.top().second=true;
        }
        else if(c==')'){
            st.pop();
        }
    }
    return root;
}

//2.Generate Preorder Form (Recursive)
void preorder(Node *root){
    if (root==nullptr) return;
    cout<<root->data;
    preorder(root->left);
    preorder(root->right);
}

//3.Generate Inorder Form (Using Linear ADT)
void InOrder(Node *root){
    stack<Node *>st;
    Node *curr=root;
    while(curr!=nullptr || !st.empty()){
        while(curr!=nullptr){
            st.push(curr);
            curr=curr->left;
        }
        curr=st.top();
        st.pop();
        cout<<curr->data;
        curr=curr->right;
    }
}
//4.Generate Postorder Form (Iterative)
void PostOrder(Node* root){
    stack <Node *>st;
    Node *lastvisited=nullptr;
    Node *curr=root;
    while(curr!=nullptr || !st.empty()){
        if(curr!=nullptr){
            st.push(curr);
            curr=curr->left;
        }
        else{
            Node *top=st.top();
            if(top->right!=nullptr && lastvisited!=top->right){
                curr=top->right;
            }
            else{
                cout<<top->data;
                lastvisited=top;
                st.pop();
            }

        }
    }
}
//5.Validate the Tree String Without Building the Tree
bool isvalid(const string& s){
    if (s.empty()){return false;}
    stack<int> st;
    char prev='\0';
    for (char c:s){
        if (isalpha(c)) {                                       // LETTER
            if (!(prev == '\0' || prev == '(' || prev == ','))
                return false;
        }
        else if (c == '(') {                                    // KHULA BRACKET
            if (!isalpha(prev)) return false;
            st.push(0);
        }
        else if(c ==','){
            if (st.empty()){return false;}
            if (st.top()!=0){return false;}
            st.top()=1;
            }
        else if(c == ')'){
            if (st.empty()){return false;}
            if (st.top()!=1){return false;}
            st.pop();
        }
        else{
            return false;
        }
        prev=c;
    }
    return st.empty();
}
//6.Calculate the Height and Depth of the Tree
int height(Node *root){
    if (root==nullptr) return -1;
    int lh=height(root->left);
    int rh=height(root->right);
    return 1+max(lh,rh);
}
void depth(Node* root,int d){
if (root == nullptr) return;

    cout << root->data << " : depth " << d << endl;

    depth(root->left,  d + 1);
    depth(root->right, d + 1);
}
int main() {
    string s = "a(b(d,e),c(,f(g,)))";

    if (!isvalid(s)) {
        cout << "Invalid string!" << endl;
        return 0;
    }

    Node* root = buildTree(s);

    cout << "Preorder:  "; preorder(root);  cout << endl;
    cout << "Inorder:   "; InOrder(root);   cout << endl;
    cout << "Postorder: "; PostOrder(root); cout << endl;

    cout << "Height of tree: " << height(root) << endl;
    cout << "Depth of each node:" << endl;
    depth(root, 0);

    return 0;
}