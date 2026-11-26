#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
struct Node {
    T key;
    Node *left;
    Node *right;
};

template <typename T>
class Tree{
private:
    Node<T> *root = nullptr;
    int count =0;

    Node<T> *makeNode(T v) {
        Node<T> *n = new Node<T>;
        n->key = v;
        n->left= nullptr;
        n->right= nullptr;
        return n;
    }

    void printNode(ostream &out, Node<T> *n) {
        if (n == nullptr) {
            return;
        }
        printNode(out, n->left);
        out << n->key << " ";
        printNode(out, n->right);
    }

    void deleteNode(Node<T> *n) {
        if(n == nullptr) {
            return;
        }
        deleteNode(n->left);
        deleteNode(n->right);
        delete n;
    }

public:
    void insert(T v) {
        if(root == nullptr) {
            root = makeNode(v);
            count++;
            return;
        }
        Node<T> *p = root;
        while (true) {
            if(v == p->key) {
                return;
            }
            if(v < p->key) {
                if (p->left == nullptr) {
                    p->left = makeNode(v);
                    count++;
                    return;
                }
                p = p->left;
            } else{
                if(p->right == nullptr) {
                    p->right = makeNode(v);
                    count++;
                    return;
                }
                p = p->right;
            }
        }
    }

    bool contains(T v) {
        if(root== nullptr){
            return false;
        }
        Node<T> *p = root;
        while (true) {
            if (v == p->key){
                return true;
            }
            if (v < p->key) {
                if (p->left == nullptr){
                    return false;
                }
                p = p->left;
            } else {
                if (p->right == nullptr){
                    return false;
                }
                p = p->right;
            }
        }
    }

    int size(){
        return count;
    }

    void print(ostream &out){
        printNode(out, root);
    }

    ~Tree() {
        deleteNode(root);
    }
};

template <typename T>
ostream &operator<<(ostream &out, Tree<T> &t) {
    t.print(out);
    return out;
}

int main() {
    Tree<int> t;
    int q;
    cin >>q;
    char cmd[20];
    for (int i= 0; i< q; i++) {
        cin >> cmd;
        if (strcmp(cmd, "insert") == 0) {
            int v;
            cin >> v;
            t.insert(v);
        } else if(strcmp(cmd, "contains") == 0) {
            int v;
            cin >> v;
            if (t.contains(v)) cout << "Yes" << endl;
            else cout << "No" << endl;
        } else if (strcmp(cmd, "size") == 0) {
            cout << t.size() << endl;
        } else if (strcmp(cmd, "print") == 0) {
            cout<< t<< endl;
        }
    }
}