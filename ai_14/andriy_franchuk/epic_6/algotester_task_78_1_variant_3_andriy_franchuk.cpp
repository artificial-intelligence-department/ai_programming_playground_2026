#include <iostream>
#include <string>

using namespace std;

struct Node{
    int key;
    Node* right;
    Node* left;
};

struct BST{
    Node* head = nullptr;

    int count = 0;
    void insert(int value, Node*& node) {
        if (node == nullptr) {
            node = new Node{value, nullptr, nullptr};
            count++;
            return;
        }

        if (value < node->key) {
            insert(value, node->left);
        }
        else if (value > node->key) {
            insert(value, node->right);
        }
    }

    void insert(int value) {
        insert(value, head);
    }

    bool find = false;
    void contains(int value, Node*& node){
        if(node == nullptr){
            return;
        }
        if(value == node->key){
            find = true;
            return;
        }
        if (value < node->key) {
            contains(value, node->left);
        }
        else if (value > node->key) {
            contains(value, node->right);
        }
    }

    void contains(int value){
        find = false;
        contains(value, head);
        cout << (find ? "Yes":"No") << endl;
    }

    void size(){
        cout << count << endl;
    }

    void print(ostream& out, Node*& node){
        if(node == nullptr){
            return;
        }

        print(out, node->left);
        out << node->key << " ";
        print(out, node->right);
    }

    void print(ostream& out){
        print(out, head);
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    void clear(){
        clear(head);
    }
};

ostream& operator<<(ostream &os, BST& tree) {
    tree.print(os);
    return os << endl;
}

int main(){
    BST tree;
    int Q;
    cin >> Q;

    for(int i = 0; i < Q; i++){
        string command;
        cin >> command;

        if (command == "insert") {
            int value;
            cin >> value;
            tree.insert(value);
        }
        else if (command == "contains") {
            int value;
            cin >> value;
            tree.contains(value);
        }
        else if (command == "size") {
            tree.size();
        }
        else if (command == "print") {
            cout << tree;
        }
    }
    tree.clear();
}