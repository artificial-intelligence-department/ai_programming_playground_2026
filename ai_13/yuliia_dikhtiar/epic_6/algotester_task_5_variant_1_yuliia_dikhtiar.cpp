/*
Назва задачі: Lab 5v1
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <cstdio>

struct Node {
    int value;
    Node* next;
};

void append(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node{value, nullptr};

    if (head == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
    }

    tail = newNode;
}

void castSpell(Node* head, int selectedRow, int selectedCol) {
    Node* current = head;
    int index = 0;

    while (current != nullptr) {
        int row = index / 8;
        int col = index % 8;

        if (row == selectedRow || col == selectedCol) {
            current->value = 1 - current->value;
        }

        current = current->next;
        index++;
    }
}

unsigned long long getNumber(Node* head) {
    unsigned long long result = 0;
    unsigned long long weight = 1;

    Node* current = head;

    while (current != nullptr) {
        if (current->value == 1) {
            result += weight;
        }

        current = current->next;

        if (current != nullptr) {
            weight *= 2;
        }
    }

    return result;
}

void clearList(Node*& head, Node*& tail) {
    while (head != nullptr) {
        Node* oldhead = head;
        head = head->next;
        delete oldhead;
    }

    tail = nullptr;
}

int main() {
    unsigned long long a;
    int n;

    scanf("%llu", &a);
    scanf("%d", &n);

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < 64; i++) {
        int value = a % 2;
        append(head, tail, value);
        a /= 2;
    }

    for (int i = 0; i < n; i++) {
        int row, col;
        scanf("%d %d", &row, &col);

        castSpell(head, row - 1, col - 1);
    }

    unsigned long long b = getNumber(head);
    printf("%llu\n", b);

    clearList(head, tail);

    return 0;
}