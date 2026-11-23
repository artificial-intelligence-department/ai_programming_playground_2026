//Проскурня Дмитро ШІ-13
//Лабораторна робота №10, варіант 9: двонаправлений список з ключовим полем int.
//Знищити K елементів перед елементом із заданим номером, додати K елементів у кінець списку.

#include <cstdio>
#include <cstring>
#include <cctype>

struct Node {
    int key;
    Node* prev;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
    int size;
};

List createList();
void pushBack(List& list, int key);
Node* getNth(const List& list, int number);
void removeNode(List& list, Node* node);
bool deleteBefore(List& list, int number, int k);
void addToEnd(List& list, int k);
void printList(const List& list);
void destroyList(List& list);
bool readInt(int& value);

// Головна функція: створює список, заповнює його, знищує K елементів перед
// елементом із заданим номером, додає K елементів у кінець і друкує список
// після кожної зміни. Наприкінці знищує список
int main() {
    List list = createList();
    printf("Створено порожній список.\n");
    printList(list);

    int n;
    printf("\nКількість елементів списку: ");
    if (!readInt(n) || n < 1 || n > 1000) {
        printf("Помилка: кількість має бути цілим числом від 1 до 1000.\n");
        return 1;
    }

    printf("Введіть %d ключів (кожен в окремому рядку):\n", n);
    for (int i = 0; i < n; i++) {
        int key;
        while (true) {
            printf("Ключ %d: ", i + 1);
            if (readInt(key)) break;
            printf("Помилка: ключ має бути цілим числом.\n");
        }
        pushBack(list, key);
    }
    printf("\nСформований список:\n");
    printList(list);

    int number, k;
    printf("\nНомер елемента: ");
    if (!readInt(number)) {
        printf("Помилка: номер має бути цілим числом.\n");
        destroyList(list);
        return 1;
    }
    printf("Скільки елементів знищити перед ним (K): ");
    if (!readInt(k)) {
        printf("Помилка: K має бути цілим числом.\n");
        destroyList(list);
        return 1;
    }

    if (deleteBefore(list, number, k)) {
        printf("\nПісля знищення %d елементів перед елементом №%d:\n", k, number);
        printList(list);
    }

    printf("\nСкільки елементів додати в кінець (K): ");
    if (!readInt(k) || k < 1 || k > 1000) {
        printf("Помилка: K має бути цілим числом від 1 до 1000.\n");
        destroyList(list);
        return 1;
    }
    addToEnd(list, k);
    printf("\nПісля додавання %d елементів у кінець:\n", k);
    printList(list);

    destroyList(list);
    printf("\nСписок знищено.\n");
    printList(list);

    return 0;
}

// ---------- функції для роботи зі списком ----------

// Створює порожній список: head і tail нульові, розмір 0
List createList() {
    List list;
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
    return list;
}

// Створює новий вузол і додає його в кінець списку,
// оновлюючи tail, а для порожнього списку ще й head
void pushBack(List& list, int key) {
    Node* node = new Node;
    node->key = key;
    node->next = nullptr;
    node->prev = list.tail;

    if (list.tail != nullptr) {
        list.tail->next = node;
    } else {
        list.head = node;
    }
    list.tail = node;
    list.size++;
}

// Повертає вказівник на елемент із номером number (нумерація з 1)
// або nullptr, якщо такого елемента немає
Node* getNth(const List& list, int number) {
    if (number < 1 || number > list.size) {
        return nullptr;
    }
    Node* p = list.head;
    for (int i = 1; i < number; i++) {
        p = p->next;
    }
    return p;
}

// Вилучає вузол з будь-якого місця списку (голова, середина, хвіст)
// з правильним оновленням prev, next, head і tail та звільняє його
void removeNode(List& list, Node* node) {
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        list.head = node->next;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        list.tail = node->prev;
    }

    delete node;
    list.size--;
}

// Знищує K елементів, що стоять безпосередньо перед елементом із номером number.
// Якщо номер некоректний або перед елементом менше ніж K елементів,
// виводить повідомлення й список не змінює. Повертає true, якщо знищення виконано
bool deleteBefore(List& list, int number, int k) {
    Node* target = getNth(list, number);
    if (target == nullptr) {
        printf("Помилка: елемента з номером %d немає (у списку %d елементів).\n", number, list.size);
        return false;
    }
    if (k < 1) {
        printf("Помилка: K має бути додатним числом.\n");
        return false;
    }
    if (k > number - 1) {
        printf("Помилка: перед елементом №%d лише %d елементів, знищити %d неможливо.\n",
               number, number - 1, k);
        return false;
    }

    for (int i = 0; i < k; i++) {
        removeNode(list, target->prev);
    }
    return true;
}

// Зчитує K ключів і додає їх по одному в кінець списку
void addToEnd(List& list, int k) {
    printf("Введіть %d ключів (кожен в окремому рядку):\n", k);
    for (int i = 0; i < k; i++) {
        int key;
        while (true) {
            printf("Ключ %d: ", i + 1);
            if (readInt(key)) break;
            printf("Помилка: ключ має бути цілим числом.\n");
        }
        pushBack(list, key);
    }
}

// Друкує список від head до tail з номерами елементів і розміром.
// Якщо список порожній, виводить про це повідомлення
void printList(const List& list) {
    if (list.head == nullptr) {
        printf("Список порожній.\n");
        return;
    }

    printf("Розмір: %d\n", list.size);
    printf("№:    ");
    for (int i = 1; i <= list.size; i++) {
        printf("%6d", i);
    }
    printf("\nКлюч: ");
    for (Node* p = list.head; p != nullptr; p = p->next) {
        printf("%6d", p->key);
    }
    printf("\n");
}

// Знищує список: проходить від head і звільняє кожен вузол,
// після чого обнуляє head, tail і size
void destroyList(List& list) {
    Node* p = list.head;
    while (p != nullptr) {
        Node* next = p->next;
        delete p;
        p = next;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

// ---------- допоміжні функції ----------

// Зчитує рядок і розбирає з нього ціле число (можливо зі знаком мінус).
// Повертає false, якщо рядок порожній, містить сторонні символи або число завелике
bool readInt(int& value) {
    char line[64];
    if (fgets(line, sizeof(line), stdin) == nullptr) {
        return false;
    }
    line[strcspn(line, "\n")] = '\0';

    const char* p = line;
    bool negative = false;
    if (*p == '-') {
        negative = true;
        p++;
    }
    if (*p == '\0') {
        return false;
    }

    long long result = 0;
    for (; *p != '\0'; p++) {
        if (!isdigit((unsigned char)*p)) {
            return false;
        }
        result = result * 10 + (*p - '0');
        if (result > 1000000000) {
            return false;
        }
    }
    value = negative ? -result : result;
    return true;
}
