/*
Назва задачі: Lab 10 Task 1
Варіант: 1
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};

bool createList(Node*& head, int count) {
    Node* current = nullptr;

    for (int i = 0; i < count; i++) {
        int value;
        if (!(cin >> value)) {
            return false;
        }

        Node* newNode = new Node{value, nullptr};

        if (head == nullptr) {
            head = newNode;
        } else {
            current->next = newNode;
        }

        current = newNode;
    }

    return true;
}

bool insertAt(Node*& head, int position, int value) {
    if (position < 1) {
        return false;
    }

    if (position == 1) {
        head = new Node{value, head};
        return true;
    }

    Node* previous = head;
    for (int i = 1; i < position - 1 && previous != nullptr; i++) {
        previous = previous->next;
    }

    if (previous == nullptr) {
        return false;
    }

    Node* newNode = new Node{value, previous->next};
    previous->next = newNode;
    return true;
}

bool removeAt(Node*& head, int position) {
    if (position < 1 || head == nullptr) {
        return false;
    }

    if (position == 1) {
        Node* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        return true;
    }

    Node* previous = head;
    for (int i = 1; i < position - 1 && previous != nullptr; i++) {
        previous = previous->next;
    }

    if (previous == nullptr || previous->next == nullptr) {
        return false;
    }

    Node* nodeToDelete = previous->next;
    previous->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список порожній.\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        cout << current->value;
        if (current->next != nullptr) {
            cout << ' ';
        }
        current = current->next;
    }
    cout << '\n';
}

void destroyList(Node*& head) {
    while (head != nullptr) {
        Node* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

int main() {
    int count;
    cout << "Введи кількість елементів: ";
    if (!(cin >> count) || count < 0) {
        cout << "Кількість має бути невід'ємним цілим числом.\n";
        return 1;
    }

    Node* head = nullptr;
    if (count > 0) {
        cout << "Введи " << count << " цілих чисел:\n";
    }

    if (!createList(head, count)) {
        cout << "Помилка: очікувалося ціле число.\n";
        destroyList(head);
        return 1;
    }

    cout << "Початковий список: ";
    printList(head);

    int removePosition;
    cout << "Введи номер позиції для видалення: ";
    if (!(cin >> removePosition)) {
        cout << "Номер позиції має бути цілим числом.\n";
        destroyList(head);
        return 1;
    }

    if (removeAt(head, removePosition)) {
        cout << "Після видалення: ";
        printList(head);
    } else {
        cout << "Такої позиції для видалення немає.\n";
    }

    int insertPosition;
    int value;
    cout << "Введи номер позиції та число для вставки: ";
    if (!(cin >> insertPosition >> value)) {
        cout << "Очікувалися два цілі числа.\n";
        destroyList(head);
        return 1;
    }

    if (insertAt(head, insertPosition, value)) {
        cout << "Після вставки: ";
        printList(head);
    } else {
        cout << "Такої позиції для вставки немає.\n";
    }

    destroyList(head);
    cout << "Після знищення: ";
    printList(head);

    return 0;
}