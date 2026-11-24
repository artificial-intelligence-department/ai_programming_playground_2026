#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Node{
    char* key;
    Node* prev;
    Node* next;
};

struct list{
    Node* head=nullptr;
    Node* tail=nullptr;
    int size=0;
    void push(char* x){
        if(tail==nullptr){
            head=new Node{new char[strlen(x)+1], nullptr, nullptr};
            tail=head;
            strcpy(head->key, x);
        }
        else{
            tail->next=new Node{new char[strlen(x)+1], tail, nullptr};
            tail=tail->next;
            strcpy(tail->key, x);
        }
        size++;
    }
    void print(){
        if(head!=nullptr){
            for(Node* p=head; p != nullptr;p=p->next){
                cout<<p->key<<" ";
            }
        } 
        else{
            cout<<"Список порожній";
        }
    }
    void deleteEl(char x[]){
        if (head == nullptr) return;

        Node* p = head;
        while (p != nullptr && strcmp(p->key, x) != 0) {
            p = p->next;
        }
        if (p == nullptr) {
            cout<<"Немає елемента з таким ключем.\n";
            return;
        }

        if (p->prev) p->prev->next = p->next;
        else head = p->next;

        if (p->next) p->next->prev = p->prev;
        else tail = p->prev;

        delete[] p->key;
        delete p;
        size--;
        
    }

    void addByIndex(int index, char* x){
        
        if(index==size){
            push(x);
            return;
        } 
        else if(index>size){
            cout<<"Список закороткий";
            return;
        }
        if(index == 0){
            head=new Node{new char[strlen(x)+1], nullptr, head};
            head->next->prev=head;
            strcpy(head->key, x);
            size++;
            return;
        }
        Node* p=head;
        for(int i=0;i<index;i++){
            p=p->next;
        }
        p=new Node{new char[strlen(x)+1], p->prev,p};
        strcpy(p->key, x);
        p->prev->next=p;
        p->next->prev=p;
        size++;
    }
    void deleteList() {
        Node* p = head;
        while (p != nullptr) {
            Node* next = p->next;
            delete[] p->key;
            delete p;
            p = next;
        }
        head = tail = nullptr;
        size = 0;
    }
};


int main(){
    list lst;
    int n;
    cout<<"Введіть скільки елементів хочете додати: ";
    cin>>n;
    for(int i=0;i<n;i++){
        char x[256];
        x[0]='\0';
        cout<<"Введіть ключ: ";
        cin>>x;
        lst.push(x);
    }
    lst.print();
    cout<<"\nВведіть ключ елемента для видалення: ";
    char del[256];
    cin>>del;
    lst.deleteEl(del);
    lst.print();
    cout<<"\nВведіть індекс на який додадити елемент: ";
    int index;
    cin>>index;
    del[0]='\0';
    cout<<"Введіть ключ нового елемента: ";
    cin>>del;
    lst.addByIndex(index,del);
    lst.print();
    lst.deleteList();
    return 0;
}