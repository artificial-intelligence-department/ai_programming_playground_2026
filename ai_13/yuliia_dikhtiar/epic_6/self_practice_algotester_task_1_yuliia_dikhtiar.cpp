/*
Назва задачі: Максимальне щастя
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <cstdio>
#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};

void push(Node*& head, int& size, Node* candy) {
    candy->next = head;
    head = candy;
    size++;
}

void pop(Node*& head, int& size) {
    Node* oldHead = head;
    head = head->next;
    delete oldHead;
    size--;
}

int top(const Node* head) {
    return head->value;
}

Node* reverseList(Node* head) {
    Node* previous = nullptr;

    while (head != nullptr) {
        Node* next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }

    return previous;
}

int main() {
    int n;
    scanf("%d", &n);

    Node* first = nullptr;
    Node* last = nullptr;

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;

        Node* candy = new Node{value, nullptr};

        if (first == nullptr) {
            first = candy;
        } else {
            last->next = candy;
        }

        last = candy;
    }

    Node* head = nullptr;
    int size = 0;
    int score = 0;

    Node* current = first->next;
    push(head, size, first);

    while (current != nullptr) {
        Node* nextCandy = current->next;

        if (current->value == 7) {
            while (size > 1 && top(head) == 4) {
                pop(head, size);
                score += top(head) + current->value;
            }

            push(head, size, current);
        } else if (nextCandy != nullptr && top(head) == 7) {
            score += top(head) + nextCandy->value;
            delete current;
        } else {
            push(head, size, current);
        }

        current = nextCandy;
    }

    head = reverseList(head);

    if (size > 2) {
        Node* kept = head;

        if (head->value == 4) {
            kept = head->next;
        }

        for (Node* candy = kept->next; candy->next != nullptr; candy = candy->next) {
            score += kept->value + candy->next->value;
        }

        if (kept != head) {
            score += head->value + last->value;
        }
    }

    cout << score;

    while (head != nullptr) {
        pop(head, size);
    }

    return 0;
}   