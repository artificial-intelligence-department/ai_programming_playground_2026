#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* ptr;
};

// Додавання одного елемента на позицію pos (нумерація з 1)
void addAtPos(Node*& head, int pos, int number) {
    if (pos <= 1 || head == nullptr) {
        head = new Node{number, head};
        return;
    }

    Node* prev = head;
    int count = 1;
    while (prev->ptr != nullptr && count < pos - 1) {
        prev = prev->ptr;
        count++;
    }

    prev->ptr = new Node{number, prev->ptr};
}

// Знищення k елементів, починаючи з позиції pos (нумерація з 1)
void deleteKFromPos(Node*& head, int pos, int k) {
    if (head == nullptr || pos <= 0 || k <= 0) return;

    if (pos == 1) {
        int removed = 0;
        while (head != nullptr && removed < k) {
            Node* nextNode = head->ptr;
            delete head;
            head = nextNode;
            removed++;
        }
        return;
    }

    Node* prev = head;
    int count = 1;
    while (prev->ptr != nullptr && count < pos - 1) {
        prev = prev->ptr;
        count++;
    }

    int removed = 0;
    while (prev->ptr != nullptr && removed < k) {
        Node* target = prev->ptr;
        prev->ptr = target->ptr;
        delete target;
        removed++;
    }
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список порожній" << endl;
        return;
    }
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->ptr;
    }
    cout << endl;
}

int main() {
    int len, n;
    Node* head = nullptr;

    cout << "Введіть початкову кількість елементів: ";
    cin >> len;
    cout << "Введіть початкові елементи: ";
    for (int i = 0; i < len; i++) {
        cin >> n;
        // Додаємо в кінець, щоб порядок збігався з уведеним
        addAtPos(head, i + 1, n);
    }

    cout << "Початковий список: ";
    printList(head);

    int delPos, delK;
    cout << "Введіть номер елемента, з якого почати видалення: ";
    cin >> delPos;
    cout << "Введіть кількість елементів, які треба видалити: ";
    cin >> delK;
    deleteKFromPos(head, delPos, delK);
    cout << "Список після видалення: ";
    printList(head);

    int addPos, addK;
    cout << "Введіть номер позиції, звідки почати додавання нових елементів: ";
    cin >> addPos;
    cout << "Введіть кількість нових елементів: ";
    cin >> addK;
    cout << "Введіть нові елементи: ";
    for (int i = 0; i < addK; i++) {
        int a;
        cin >> a;
        addAtPos(head, addPos + i, a);
    }

    cout << "Новий список: ";
    printList(head);

    while (head != nullptr) {
        Node* tmp = head->ptr;
        delete head;
        head = tmp;
    }

    return 0;
}