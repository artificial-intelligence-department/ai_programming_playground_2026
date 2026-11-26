#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
};
Node *makeNode(int v){
    Node *n=new Node;
    n->key= v;
    n->left =nullptr;
    n->right= nullptr;
    return n;
}
struct Tree{
    Node *root= nullptr;
    int count = 0;
};
void insert(Tree &t, int v) {
    if (t.root== nullptr) {
        t.root= makeNode(v);
        t.count++;
        return;
    }
    Node *p = t.root;
    while (true) {
        if (v == p->key){
            return;
        }
        if (v < p->key){
            if (p->left== nullptr) {
                p->left= makeNode(v);
                t.count++;
                return;
            }
            p= p->left;
        } else{
            if (p->right == nullptr) {
                p->right = makeNode(v);
                t.count++;
                return;
            }
            p= p->right;
        }
    }
}
bool contains(Tree &t, int v){
    if (t.root == nullptr) {
        return false;
    }
    Node *p =t.root;
    while (true) {
        if (v ==p->key){
            return true;
        }
        if (v < p->key){
            if (p->left == nullptr){
                return false;
            }
            p = p->left;
        } else{
            if (p->right == nullptr) {
                return false;
            }
            p =p->right;
        }
    }
}

void printNode(ostream &out, Node *n) {
    if (n == nullptr){
        return;
    }
    printNode(out, n->left);
    out << n->key << " ";
    printNode(out, n->right);
}

ostream &operator<<(ostream &out, Tree &t){
    printNode(out, t.root);
    return out;
}

void deleteNode(Node *n) {
    if (n == nullptr){
        return;
    }
    deleteNode(n->left);
    deleteNode(n->right);
    delete n;
}

int main() {
    Tree t;
    int q;
    cin >> q;
    char cmd[20];
    for (int i = 0; i < q; i++){
        cin >> cmd;
        if (strcmp(cmd, "insert") == 0) {
            int v;
            cin >> v;
            insert(t, v);
        } else if (strcmp(cmd, "contains") == 0) {
            int v;
            cin >> v;
            if (contains(t, v)) cout << "Yes" << endl;
            else cout << "No" << endl;
        } else if (strcmp(cmd, "size") == 0){
            cout << t.count << endl;
        } else if (strcmp(cmd, "print") == 0){
            cout << t << endl;
        }
    }
    deleteNode(t.root);
}