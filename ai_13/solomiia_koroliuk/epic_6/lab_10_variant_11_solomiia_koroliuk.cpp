#include <cstdio> //засоби C вводу і виводу
#include <cstring> //функції C рядків

using namespace std;

const int MAX_KEY = 64;   // розмір буфера для ключа (63 символи + '\0')

// ---------- Структури ----------

// Вузол: ключ — динамічний рядок, який вузол створює і звільняє сам
struct Node {
    char *key;
    Node *next;
    Node *prev;
};

// Розмір і вказівники на перший та останній елементи
struct DblList {
    int size;
    Node *head;
    Node *tail;
};

// ---------- Прототипи функцій ----------
void flushLine();
DblList *createList();
Node *newNode(const char *key);
void pushBack(DblList *list, const char *key);
bool insertAt(DblList *list, int pos, const char *key);
bool deleteByKey(DblList *list, const char *key);
void printList(const DblList *list);
void deleteList(DblList *&list);

int main() {
    DblList *list = createList(); // 1. створення (порожнього) списку

    printf("Порожній список: ");
    printList(list); // перевірка повідомлення для порожнього списку

    int n;
    printf("Введіть кількість елементів списку: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Помилка: потрібне невідʼємне ціле число.\n");
        deleteList(list);
        return 1;
    }
    flushLine();

    char buf[MAX_KEY];

    for (int i = 0; i < n; i++) {
        printf("Елемент %d: ", i + 1);
        if (scanf("%63s", buf) != 1) {  // читаємо одне слово, не більше 63 символів
            printf("Помилка: ключ не введено.\n");
            deleteList(list);
            return 1;
        }
        flushLine();
        pushBack(list, buf); // 2. додавання в кінець під час формування
    }

    printf("Список: ");
    printList(list);

    // 3. знищення елемента із заданим ключем
    printf("Введіть ключ елемента для знищення: ");
    if (scanf("%63s", buf) == 1) {
        flushLine();
        if (deleteByKey(list, buf)) {
            printf("Елемент \"%s\" знищено.\n", buf);
        } else {
            printf("Елемента з ключем \"%s\" немає, нічого не знищено.\n", buf);
        }
        printf("Список: ");
        printList(list);
    }

    // 2. додавання елемента із зазначеним номером
    int pos;
    printf("Введіть номер, який матиме новий елемент (від 1 до %d): ", list->size + 1);
    if (scanf("%d", &pos) == 1) {
        flushLine();
        printf("Введіть ключ нового елемента: ");
        if (scanf("%63s", buf) == 1) {
            flushLine();
            if (insertAt(list, pos, buf)) {
                printf("Елемент \"%s\" додано під номером %d.\n", buf, pos);
            } else {
                printf("Помилка: номер має бути від 1 до %d, елемент не додано.\n", list->size + 1);
            }
            printf("Список: ");
            printList(list);
        }
    }

    deleteList(list); // 5. знищення списку
    printf("Список знищено.\n");

    return 0;
}


// ---------- Допоміжні функції ----------

// Відкидає залишок поточного рядка у вхідному потоці
void flushLine() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // просто читаємо до кінця рядка
    }
}

// Створює вузол із власною копією ключа
Node *newNode(const char *key) {
    Node *node = new Node;
    node->key = new char[strlen(key) + 1];   // памʼять рівно під довжину ключа + '\0'
    strcpy(node->key, key);
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}


// ---------- Функції для роботи зі списком ----------

// 1. Створення порожнього списку
DblList *createList() {
    DblList *list = new DblList;
    list->size = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

// Додавання в кінець списку
void pushBack(DblList *list, const char *key) {
    Node *node = newNode(key);

    node->prev = list->tail;
    if (list->tail != nullptr) {
        list->tail->next = node;
    } else {
        list->head = node; // список був порожній
    }
    list->tail = node;
    list->size++;
}

// 2. Додавання елемента так, щоб він отримав номер pos (нумерація з 1)
bool insertAt(DblList *list, int pos, const char *key) {
    if (pos < 1 || pos > list->size + 1) {
        return false;
    }

    if (pos == list->size + 1) { // у кінець (зокрема в порожній список)
        pushBack(list, key);
        return true;
    }

    // шукаємо елемент, який зараз має номер pos — новий стане перед ним
    Node *cur = list->head;
    for (int i = 1; i < pos; i++) {
        cur = cur->next;
    }

    Node *node = newNode(key);
    node->next = cur;
    node->prev = cur->prev;

    if (cur->prev != nullptr) {
        cur->prev->next = node;
    } else {
        list->head = node; // вставка на початок
    }
    cur->prev = node;
    list->size++;
    return true;
}

// 3. Знищення першого елемента із заданим ключем
bool deleteByKey(DblList *list, const char *key) {
    Node *cur = list->head;

    while (cur != nullptr && strcmp(cur->key, key) != 0) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        return false; // такого ключа немає
    }

    if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
    } else {
        list->head = cur->next;  // видаляємо голову
    }

    if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
    } else {
        list->tail = cur->prev;  // видаляємо хвіст
    }

    delete[] cur->key;
    delete cur;
    list->size--;
    return true;
}

// 4. Друк списку (з повідомленням, якщо він порожній)
void printList(const DblList *list) {
    const Node *p = list->head;

    if (p == nullptr) {
        printf("List empty!!!\n");
        return;
    }

    while (p != nullptr) {
        printf("%s ", p->key);
        p = p->next;
    }
    printf("(елементів: %d)\n", list->size);
}

// 5. Знищення списку: спочатку ключі й вузли, потім сама структура
void deleteList(DblList *&list) {
    Node *p = list->head;

    while (p != nullptr) {
        Node *next = p->next;
        delete[] p->key;
        delete p;
        p = next;
    }

    delete list;
    list = nullptr;
}
