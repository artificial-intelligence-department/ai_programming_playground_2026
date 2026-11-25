/*
Назва задачі: Дужки і Нобелівська премія
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

struct Node {
    char bracket;
    int position;
    Node* next;
};

void push(Node*& head, char bracket, int position) {
    Node* newNode = new Node{bracket, position, head};
    head = newNode;
}

int pop(Node*& head) {
    Node* oldhead = head;
    int position = oldhead->position;

    head = oldhead->next;

    delete oldhead;
    return position;
}

void clearStack(Node*& head) {
    while (head != nullptr) {
        pop(head);
    }
}

void printOrder(const char text[], const int closing[], bool printed[], int left, int right) {

    for (int i = left; i <= right; i++) {
        if (text[i] == '[' && !printed[i]) {
            int end = closing[i];

            printOrder(text, closing, printed, i + 1, end - 1);

            printf("%d %d\n", i + 1, end + 1);
            printed[i] = true;
        }
    }

    for (int i = left; i <= right; i++) {
        if (text[i] == '(' && !printed[i]) {
            int end = closing[i];

            printOrder(text, closing, printed, i + 1, end - 1);

            printf("%d %d\n", i + 1, end + 1);
            printed[i] = true;
        }
    }
}

int main() {
    char text[256];

    if (!cin.getline(text, sizeof(text))) {
        return 0;
    }

    int length = strlen(text);

    int closing[256];
    bool printed[256] = {};

    for (int i = 0; i < 256; i++) {
        closing[i] = -1;
    }

    Node* head = nullptr;
    bool valid = true;

    for (int i = 0; i < length; i++) {
        char symbol = text[i];

        if (symbol == '(' || symbol == '[') {
            push(head, symbol, i);
        }
        else if (symbol == ')' || symbol == ']') {
            if (head == nullptr) {
                valid = false;
                break;
            }

            if ((symbol == ')' && head->bracket != '(') || (symbol == ']' && head->bracket != '[')) {
                valid = false;
                break;
            }

            int openingPosition = pop(head);
            closing[openingPosition] = i;
        }
    }

    if (head != nullptr) {
        valid = false;
    }

    clearStack(head);

    if (!valid) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    printOrder(text, closing, printed, 0, length - 1);

    return 0;
}