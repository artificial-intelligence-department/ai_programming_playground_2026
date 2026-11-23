#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    char* key;
    Node* next;
    Node* prev;
};

void createList(Node*& head, Node*& tail) {
    head = nullptr;
    tail = nullptr;
}

void pushBack(Node*& head, Node*& tail, const char* value) {
    Node* newNode = new Node;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    newNode->key = new char[strlen(value)+1];
    strcpy(newNode->key, value);

    if (tail != nullptr) {
        tail->next = newNode;
        newNode->prev = tail;
    }
    else {
        head = newNode;
    }
    tail = newNode;
}

void addKElements(Node*& head, Node*& tail, int k) {
    char buffer[256];
    for (int i = 0; i < k; i++) {
        cout << "Enter key " << i + 1 << ": ";
        cin.getline(buffer, 256);

        if (buffer[0] == '\0') {
            cout << "Empty key is not allowed! Try again.\n";
            i--;
            continue;
        }

        pushBack(head, tail, buffer);
    }
}

void printForward(Node* head) {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    Node* curr = head;
    cout << "Вивід ==============" << endl;
    while (curr != nullptr) {
        cout << curr->key << " ";
        curr = curr->next;
    }
    cout << endl;
}

void deleteByKey(Node*& head, Node*& tail, const char* value) {
    if (head == nullptr) return;
    Node* curr = head;
    while(curr != nullptr) {
        if (strcmp(curr->key, value) == 0) {
            if (curr->prev != nullptr) curr->prev->next = curr->next;
            else head = curr->next;

            if (curr->next != nullptr) curr->next->prev = curr->prev;
            else tail = curr->prev;

            delete[] curr->key;
            delete curr;
            return;
        }
        curr = curr->next;
    }
}

void destroyList(Node*& head, Node*& tail) {
    Node* curr = head;

    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;

        delete[] temp->key;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    createList(head, tail);

    pushBack(head, tail, "abc");
    pushBack(head, tail, "123");
    addKElements(head, tail, 3);
    printForward(head);
    deleteByKey(head, tail, "123");
    printForward(head);
    deleteByKey(head, tail, "abc");
    printForward(head);
    destroyList(head, tail);
    return 0;
}