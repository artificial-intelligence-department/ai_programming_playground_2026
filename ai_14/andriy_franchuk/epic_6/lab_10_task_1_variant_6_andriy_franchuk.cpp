#include <iostream>

using namespace std;

struct Node{
    int key;
    Node* next;
    Node* prev;
};

void add(Node* &head, int value){
    Node* new_element = new Node{value, nullptr, nullptr};
    Node* p = head;
    Node* last = nullptr;
    for( ;p != nullptr; p=p->next){
        last = p;
    }
    if(last == nullptr){
        head = new_element;
        return;
    }
    new_element->prev = last;
    last->next = new_element;
}

void print(Node* head){
    Node* p = head;
    if(p == nullptr){
        cout << "Список пустий" << endl;
        return;
    }
    for( ;p != nullptr; p=p->next){
        cout << p->key << " ";
    }
    cout << endl;
}

void del(Node* &head, int pos){
    Node* p = head;
    for(int i = 0; i < pos - 1; i++, p = p->next){
        if(p == nullptr){
            cout << "Такого елемента нема" << endl;
            return;
        }
    }
    if(p == nullptr){
            cout << "Такого елемента нема" << endl;
            return;
    }
    Node* tmp = nullptr;
    if(p->prev != nullptr){
        tmp = p->prev->next;
        p->prev->next = p->next;
    }else{
        head = p->next;
    }
    if(p->next != nullptr){
        p->next->prev = tmp;
    }
    delete p;
    
}

void addBegin(Node* &head, int value){
    if(head == nullptr){
        head = new Node{value, head, nullptr};
        return;
    }
    Node* new_element = new Node{value, head, nullptr};
    head->prev = new_element;
    head = new_element;
}

void delete_list(Node* &head){
    Node* p = head;
    Node* last = head;
    for( ;p != nullptr;){
        last = p->next;
        delete p;
        p = last;
    }
    head = nullptr;
}

int main(){
    Node* head = nullptr;

    int n;
    cin >> n;

    int value;
    for(int i = 0; i < n; i++){
        cin >> value;
        add(head, value);
    }
    print(head);

    int pos;
    cin >> pos;
    if(pos > 0){
        del(head, pos);
        print(head);
    }else{
        cout << "Неправильний індекс" << endl;
    }

    cin >> value;
    addBegin(head, value);
    print(head);

    delete_list(head);
}