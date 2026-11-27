#include <iostream>
using namespace std;

struct Node {
    Node* next = nullptr;
    int key = 0;
};

void pushBack(Node *&head, int key){
    Node* q = new Node{nullptr, key};
    if(head == nullptr){
        head = q;
        return;
    }
    Node* cur = head;
    while(cur->next != nullptr){
        cur = cur->next;
    }
    cur->next = q;
}

bool removeByKey(Node *&head, int key){
    if(head == nullptr){
        return false;
    }
    if(head->key == key){
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* prev = head;
    while(prev->next != nullptr && prev->next->key != key){
        prev = prev->next;
    }
    if(prev->next == nullptr){
        return false;
    }
    Node* cur = prev->next;
    prev->next = cur->next;
    delete cur;
    return true;
}

ostream& operator<<(ostream &os, const Node &node){
    return os << node.key;
}

void printList(const Node* head){
    if(head == nullptr){
        cout << "Список пустий" << endl;
        return;
    }
    cout << "Список: ";
    for(const Node* p = head; p; p = p->next){
        cout << *p << " ";
    }
    cout << endl;
}

void clear(Node *&head){
    while(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){
    Node* head = nullptr;
    int choice;

    do {
        cout << "\n===== Меню =====\n"
             << "1) pushBack\n"
             << "2) removeByKey\n"
             << "3) printList\n"
             << "0) Вихід\n"
             << "Ваш вибір: ";
        cin >> choice;

        switch(choice){
            case 1: {
                int n;
                cout << "Введіть елемент, який хочете додати: ";
                cin >> n;
                pushBack(head, n);
                printList(head);
                break;
            }
            case 2: {
                if(head == nullptr){
                    cout << "Помилка: список пустий!" << endl;
                    break;
                }
                int n;
                cout << "Введіть елемент, який хочете видалити: ";
                cin >> n;
                if(removeByKey(head, n)){
                    cout << "Видалено." << endl;
                    printList(head);
                } else {
                    cout << "Помилка: елемента з таким значенням не знайдено" << endl;
                }
                break;
            }
            case 3:
                printList(head);
                break;
            case 0:
                cout << "Завершення програми..." << endl;
                break;
            default:
                cout << "Невідома команда, введіть ще раз" << endl;
        }
    } while(choice != 0);


    clear(head);
    return 0;
}