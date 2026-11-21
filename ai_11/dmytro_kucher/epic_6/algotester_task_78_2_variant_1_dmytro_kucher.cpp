/*
Епік 6. Завдання з Алготестера. Лабораторна робота №78. Завдання №2. Варіант №1
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Node {
    T key;
    Node<T>* next;
    Node<T>* prev;
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

    Node<T>* findNode(int index) {
        Node<T>* p = head;

        for (int i = 0; i < index; i++) {
            p = p->next;
        }

        return p;
    }

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    void insert (int index, int n, const T* arr) {

        if (index < 0 || index > count) return;

        Node<T>* current;

        if (index == count) current = nullptr;
        else current = findNode(index);

        for (int i = 0; i<n; i++) {

            Node<T>* newNode = new Node<T>;
            newNode->key = arr[i];

            if (current == nullptr) {

                newNode->next = nullptr;
                newNode->prev = tail;

                if (tail != nullptr) tail->next = newNode;
                else head = newNode;

                tail = newNode;
            }

            else {
                newNode->next = current;
                newNode->prev = current->prev;
        
                if (current->prev != nullptr) current->prev->next = newNode;
                else head = newNode;

                current->prev = newNode;
            }

            count++;
        }
    }

    void erase (int index, int n) {

        if (index < 0 || n < 0 || index > count || n > count) return;
        if (n==0) return;

        Node<T>* current = findNode(index);

        for (int i = 0; i<n; i++) {

            Node<T>* nextN = current->next;

            if (current->prev != nullptr) current->prev->next = current->next;
            else head = current->next;

            if (current->next != nullptr) current->next->prev = current->prev;
            else tail = current->prev;
            
            delete current;
            current = nextN;

            count--;
        }
    }

    int size () const {
        return count;
    }

    T get (int index) {

        Node<T>* node = findNode(index);
        return node->key;

    }

    void set (int index, T value) {

        Node<T>* node = findNode(index);
        node->key = value;

    }    

    friend ostream& operator<<(ostream& out, const DoublyLinkedList<T>& list) {

        Node<T>* p = list.head;

        while (p != nullptr) {

            out << p->key;
            if (p->next != nullptr) out << " ";
            p = p->next;
        }

        return out;
    }

    ~DoublyLinkedList () {

        Node<T>* p = head;

        while (p != nullptr) {
            Node<T>* temp = p;
            p = p->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        count = 0;
    }

};



int main () {

    int Q;
    cin >> Q;

    DoublyLinkedList<int> list;

    for (int i = 0; i<Q; i++) {

        string choice;
        cin >> choice;

        if (choice == "insert") {

            int index, N;
            cin >> index >> N;

            int* arr = new int[N];

            for (int i = 0; i<N; i++) {
                cin >> arr[i];
            }

            list.insert(index, N, arr);
            delete[] arr;
        }
   
        else if (choice == "erase") {

            int index, n;
            cin >> index >> n;

            list.erase(index, n);
        }

        else if (choice == "size") cout << list.size() << "\n";
   
        else if (choice == "get") {

            int index;
            cin >> index;

            cout << list.get(index) << "\n";
        }
    
        else if (choice == "set") {

            int index, value;
            cin >> index >> value;
        
            list.set(index, value);
        }
    
        else if (choice == "print") cout << list << "\n";
    
    }

    return 0;
}