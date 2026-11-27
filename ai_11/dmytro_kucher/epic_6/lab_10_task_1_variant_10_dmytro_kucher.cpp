/*
Епік 6. Лабораторна робота №10. Завдання №1. Варіант №10
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* next;
    Node* prev;
};

void deleteList (Node*& head, Node*& tail) {

    while (head != nullptr) {
        Node* t = head;
        head = head->next;
        delete t;
    }

    tail = nullptr;
}

void createDoublyLisnkedList (Node*& head, Node*& tail) {

    deleteList(head, tail);

    head = nullptr;
    tail = nullptr;
 
    cout << "Список успішно створено\n";
}

void showList (Node* head) {

    if (head == nullptr) {
        cout << "Списка не існує, або він пустий!\n";
        return;
    }

    Node* p = head;

    while (p != nullptr) {
        cout << p->key << " ";
        p = p->next;
    }
    cout << "\n";
}

void addElementToList (Node*& head, Node*& tail, int number, int value) {

    Node* p = head;
    int i = 1;

    while (p != nullptr && i < number) {
        p = p->next;
        i++;
    }

    if (p != nullptr) {
        p->key = value;
        return;
    }

    int count = 0;
    p = head;

    while (p != nullptr) {
        count++;
        p = p->next;
    }

    for (int j = count+1; j <= number; j++) {

        Node* node = new Node;

        node->key = (j == number) ? value : 0;
        node->next = nullptr;
        node->prev = tail;

        if (tail == nullptr) head = node;
        else tail->next = node;

        tail = node;
    }
}

void removeElementFromList (Node*& head, Node*& tail, int number) {

    int count = 0;
    Node* p = head;

    while (p != nullptr) {
        count++;
        p = p->next;
    }

    if (number > count) {
        cout << "Помилка! У списку лише " << count << " елементів!\n";
        return;
    }

    for (int i = 0; i<number; i++) {

        if (tail == nullptr) {
            cout << "Список пустий!\n";
            return;
        }

        Node* p = tail;
        tail = p->prev;

        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;

        delete p;
    }
}

int main () {

    bool isAlive = true;

    Node* head = nullptr;
    Node* tail = nullptr;

    do {

        int choice;
        cout << "\n=========== Меню ===========\n";
        cout << "1  Створити пустий список\n";
        cout << "2  Показати список\n";
        cout << "3  Додати елемент\n";
        cout << "4  Видалити K елементів з кінця\n";
        cout << "0  Вийти\n";
        cout << "Введіть операцію: ";
        cin >> choice;

        if (!cin || choice > 4 || choice < 0) {
            cout << "Некоректні вхідні дані!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
    
        else if (choice == 0) {
            isAlive = false;
            deleteList (head, tail);
        }

        else if (choice == 1) createDoublyLisnkedList (head, tail);

        else if (choice == 2) showList (head);

        else if (choice == 3) {

            int n, k;
            cout << "Введіть номер елементу, який хочете додати, та його значення: ";
            cin >> n >> k;

            if (!cin || n < 1 || n > 20) {
                cout << "Некоректні вхідні дані!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            addElementToList (head, tail, n, k);
        }
        
        else if (choice == 4) {

            int r;
            cout << "Введіть кількість елементів, яку хочете видалити: ";
            cin >> r;

            if (!cin || r < 0) {
                cout << "Некоректні вхідні дані!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            removeElementFromList (head, tail, r);
        }

    } while (isAlive);

    deleteList (head, tail);

    return 0;
}