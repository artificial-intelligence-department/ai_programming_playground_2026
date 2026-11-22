/*Epic 6 - Завдання 1 лабораторної 10 варіант 19
Чернихівський Максим
Ші - 14*/


#include <iostream>
#include <cstring>

using namespace std;

const int MAX_KEY = 64;
const int MAX_K = 20;

struct Node {
    char *key;
    Node *prev;
    Node *next;
};

struct List {
    Node *head;
    Node *tail;
    int size;
};

void initList(List &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

// Створює вузол і копіює в нього ключ
Node* createNode(const char *key) {
    Node *node = new Node;
    node -> key = new char[strlen(key) + 1];
    strcpy(node -> key, key);
    
    node -> prev = nullptr;
    node -> next = nullptr;

    return node;
}

// Додає елемент в кінець
void addToEnd(List &list, const char *key) {
    Node *node = createNode(key);
    
    if (list.head == nullptr) {
        list.head = node;
        list.tail = node;
    } else {
        list.tail -> next = node;
        node -> prev = list.tail;
        list.tail = node;
    }
    list.size++;    
}

// Додає елемент в початок  
void addToFront(List &list, const char *key) {
    Node *node = createNode(key);
    
    if (list.head == nullptr) {
        list.head = node;
        list.tail = node;
    } else {
        list.head -> prev = node;
        node -> next = list.head;
        list.head = node;
    }
    list.size++;    
}

// Додає k ключів на початок, зберігаючи їхній порядок.
void addKToFront(List &list, char keys[][MAX_KEY], int k) {
    for (int i = k - 1; i >= 0; i--) {
        addToFront(list, keys[i]);
    }
}

// Вилучає вузол зі списку і звільняє його пам'ять
void removeNode(List &list, Node *node) {
    if (node -> prev != nullptr) {
        node -> prev -> next = node -> next;
    } else {
        list.head = node -> next;
    }
    
    if (node -> next != nullptr) {
        node -> next -> prev = node -> prev;
    } else {
        list.tail = node -> prev;
    }

    delete[] node -> key;
    delete node;
    list.size--;
}

// Перевіряє, чи є номер position серед вибраних номерів
bool isNumberChosen(const int *numbers, int k, int position) {
    for (int i = 0; i < k; i++) {
        if (numbers[i] == position) {
            return true;
        }
    }
    return false;
}

// Перевіряє номери: кожен має бути від 1 до size, без повторів
bool validateNumbers(const int *numbers, int k, int size) {
    for (int i = 0; i < k; i++) {
        if (numbers[i] < 1 || numbers[i] > size) {
            return false;
        }
        for (int j = 0; j < k; j++) {
            if (numbers[i] == numbers[j] && i != j) {
                return false;
            }
        }
    }
    return true;
}

// Видаляє елементи за номерами (нумерація з 1).
bool removeByNumbers(List &list, const int *numbers, int k) {
    if (!validateNumbers(numbers, k, list.size)) {
        return false;
    }
    int position = 1;
    Node *current = list.head;
    while (current != nullptr) {
        Node *next = current -> next;
        if (isNumberChosen(numbers, k, position)) {
            removeNode(list, current);
        }
        position++;
        current = next;
    }
    return true;
}

void printList(const List &list) {
    if (list.head == nullptr) {
        cout << "Список порожній.\n";
        return;
    }
    cout << "Список (" << list.size << "): ";
    for (const Node *p = list.head; p != nullptr; p = p -> next) {
        cout << p -> key;
        if (p -> next != nullptr) {
            cout << " <-> ";
        }
    }
    cout << "\n";
}

// Звільняє пам'ять
void destroyList(List &list) {
    while (list.head != nullptr) {
        removeNode(list, list.head);
    }
}

// Читає число
bool readCount(const char *prompt, int max, int &value) {
    cout << prompt;
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    cin.ignore(10000, '\n');
    return value >= 0 && value <= max;
}

// Читає рядок - ключ
bool readKey(char *buf) {
    cin.getline(buf, MAX_KEY);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return buf[0] != '\0';
}

int main() {
    List list;
    initList(list);

    int n;
    if (!readCount("Кількість елементів у списку: ", 1000, n)) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        char key[MAX_KEY];
        cout << "Ключ " << i + 1 << ": ";
        if (!readKey(key)) {
            cout << "Помилка: ключ має містити від 1 до " << MAX_KEY - 1 << " символів.\n";
            destroyList(list);
            return 1;
        }
        addToEnd(list, key);
    }
    cout << "Початковий список: ";
    printList(list);

    int k;
    if (!readCount("Скільки елементів видалити (K): ", MAX_K, k)) {
        cout << "Помилка: K має бути цілим числом від 0 до " << MAX_K << ".\n";
        destroyList(list);
        return 1;
    }
    int numbers[MAX_K];
    for (int i = 0; i < k; i++) {
        if (!readCount("Номер елемента (індекс першого елемента - 1): ", 1000000, numbers[i])) {
            cout << "Помилка: номер має бути цілим числом.\n";
            destroyList(list);
            return 1;
        }
    }
    if (removeByNumbers(list, numbers, k)) {
        cout << "Після видалення: ";
    } else {
        cout << "Помилка: номери мають бути від 1 до " << list.size << " і не повторюватися, список не змінено.\n";
    }
    printList(list);

    if (!readCount("Скільки елементів додати на початок (K): ", MAX_K, k)) {
        cout << "Помилка: K має бути цілим числом від 0 до " << MAX_K << ".\n";
        destroyList(list);
        return 1;
    }
    char keys[MAX_K][MAX_KEY];
    for (int i = 0 ; i < k; i++) {
        cout << "Ключ " << i + 1 << ": ";
        if (!readKey(keys[i])) {
            cout << "Помилка: ключ має містити від 1 до " << MAX_KEY - 1 << " символів.\n";
            destroyList(list);
            return 1;
        }
    }
    addKToFront(list, keys, k);
    cout << "Після додавання на початок: ";
    printList(list);

    destroyList(list);
    return 0;
}