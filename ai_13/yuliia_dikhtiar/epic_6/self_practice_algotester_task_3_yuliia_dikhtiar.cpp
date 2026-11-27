/*
Назва задачі: Дужкова інверсія
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <cstdio>

struct Node {
    char bracket;
    int balanceAfter;
    int minAfter;

    Node* next;
    Node* prev;
};

void append(Node*& head, Node*& tail, char bracket, int& balance) {
    if (bracket == '(') {
        balance++;
    } else {
        balance--;
    }

    Node* newNode = new Node{bracket, balance, balance, nullptr, tail};

    if (tail == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
    }

    tail = newNode;
}

void prepareMinimums(Node* tail) {
    Node* current = tail;

    while (current != nullptr) {
        current->minAfter = current->balanceAfter;

        if (current->next != nullptr && current->next->minAfter < current->minAfter) {
            current->minAfter = current->next->minAfter;
        }

        current = current->prev;
    }
}

bool canInvert(Node* head, int totalBalance, int size) {
    if (size % 2 != 0) {
        return false;
    }

    Node* left = head;
    int balanceBefore = 0;

    while (left != nullptr) {
        if (balanceBefore < 0) {
            break;
        }

        int balance = balanceBefore;
        Node* right = left;

        while (right != nullptr) {
            if (right->bracket == '(') {
                balance--;
            } else {
                balance++;
            }

            if (balance < 0) {
                break;
            }

            int shift = balance - right->balanceAfter;

            int finalBalance = totalBalance + shift;
            int minimumAfter = right->minAfter + shift;

            if (finalBalance == 0 && minimumAfter >= 0) {
                return true;
            }

            right = right->next;
        }

        balanceBefore = left->balanceAfter;
        left = left->next;
    }

    return false;
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
    Node* head = nullptr;
    Node* tail = nullptr;

    int size = 0;
    int totalBalance = 0;

    char symbol;

    while (scanf("%c", &symbol) == 1 && symbol != '\n') {
        if (symbol == '(' || symbol == ')') {
            append(head, tail, symbol, totalBalance);
            size++;
        }
    }

    prepareMinimums(tail);

    bool alreadyValid = head != nullptr && totalBalance == 0 && head->minAfter >= 0;

    if (alreadyValid || canInvert(head, totalBalance, size)) {
        printf("possible\n");
    } else {
        printf("impossible\n");
    }

    clearList(head, tail);

    return 0;
}