/*
 * Лабораторна робота № 10, варіант 3.
 * Записи в лінійному списку містять ключове поле типу int.
 * Сформувати однонаправлений список. Знищити з нього K елементів, починаючи
 * із заданого номера, додати елемент перед елементом із заданим ключем.
 */

#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *next;
};

bool readInt(const char *prompt, int low, int high, int &value) {
    bool valid = false;
    while (!valid) {
        cout << prompt;
        cin >> value;
        bool failed = cin.fail();
        bool ended = cin.eof();
        if (failed && ended) {
            return false;
        }
        if (failed) {
            cin.clear();
            cin.ignore(1000000, '\n');
            cout << "Помилка: введіть ціле число." << endl;
        } else if (value < low || value > high) {
            cout << "Помилка: число має бути від " << low << " до " << high << "." << endl;
        } else {
            valid = true;
        }
    }
    return true;
}

Node *createList() {
    return nullptr;
}

bool addToEnd(Node *&head, int key) {
    Node *node = new Node;
    node->key = key;
    node->next = nullptr;
    if (head == nullptr) {
        head = node;
        return true;
    }
    Node *last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = node;
    return true;
}

void printList(const Node *head) {
    if (head == nullptr) {
        cout << "Список порожній." << endl;
        return;
    }
    const Node *p = head;
    while (p != nullptr) {
        cout << p->key << " ";
        p = p->next;
    }
    cout << endl;
}

int deleteElements(Node *&head, int start, int count) {
    Node *previous = nullptr;
    Node *current = head;
    int position = 1;
    while (current != nullptr && position < start) {
        previous = current;
        current = current->next;
        ++position;
    }
    int deleted = 0;
    while (current != nullptr && deleted < count) {
        Node *next = current->next;
        delete current;
        current = next;
        ++deleted;
    }
    if (previous == nullptr) {
        head = current;
    } else {
        previous->next = current;
    }
    return deleted;
}

bool insertBefore(Node *&head, int key, int value) {
    Node *previous = nullptr;
    Node *current = head;
    while (current != nullptr && current->key != key) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        return false;
    }
    Node *node = new Node;
    node->key = value;
    node->next = current;
    if (previous == nullptr) {
        head = node;
    } else {
        previous->next = node;
    }
    return true;
}

void destroyList(Node *&head) {
    while (head != nullptr) {
        Node *next = head->next;
        delete head;
        head = next;
    }
}

bool fillList(Node *&head) {
    int size = 0;
    bool ok = readInt("Кількість елементів списку (1-100): ", 1, 100, size);
    if (!ok) {
        return false;
    }
    for (int i = 1; i <= size; ++i) {
        int key = 0;
        ok = readInt("Ключ елемента: ", -1000000000, 1000000000, key);
        if (!ok) {
            return false;
        }
        addToEnd(head, key);
    }
    return true;
}

bool deleteStep(Node *&head) {
    int start = 0;
    int count = 0;
    bool ok = readInt("Номер, з якого видаляти: ", 1, 1000000, start);
    if (ok) {
        ok = readInt("Кількість K елементів для видалення: ", 1, 1000000, count);
    }
    if (ok) {
        int deleted = deleteElements(head, start, count);
        cout << "Видалено елементів: " << deleted << endl;
        cout << "Список після видалення: ";
        printList(head);
    }
    return ok;
}

bool insertStep(Node *&head) {
    int key = 0;
    int value = 0;
    bool ok = readInt("Ключ, перед яким додати елемент: ", -1000000000, 1000000000, key);
    if (ok) {
        ok = readInt("Ключ нового елемента: ", -1000000000, 1000000000, value);
    }
    if (ok) {
        bool inserted = insertBefore(head, key, value);
        if (inserted) {
            cout << "Елемент додано. Список після додавання: ";
            printList(head);
        } else {
            cout << "Елемента з ключем " << key << " у списку немає, додавання не виконано." << endl;
        }
    }
    return ok;
}

int main() {
    Node *head = createList();
    bool ok = fillList(head);
    if (!ok) {
        destroyList(head);
        return 0;
    }
    cout << "Початковий список: ";
    printList(head);

    ok = deleteStep(head);
    if (ok) {
        insertStep(head);
    }

    destroyList(head);
    cout << "Список знищено: ";
    printList(head);
    return 0;
}
