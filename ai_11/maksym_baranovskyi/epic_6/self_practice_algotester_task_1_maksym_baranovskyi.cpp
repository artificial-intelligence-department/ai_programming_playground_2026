//Якийсь дивний порядок
#include <iostream>
using namespace std;

struct Node{
    Node* next = nullptr;
    int value;
};

struct List{
    Node* head = nullptr;

    ~List();
};

void pushFront(List& list, Node* node){
    node->next = list.head;
    list.head = node;
}

void insertAfter(Node* after, Node* node){
    node->next = after->next;
    after->next = node;
}

void clearList(List& list){
    while(list.head != nullptr){
        Node* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
}

List::~List(){
    clearList(*this);
}

int main(){
    int n;
    cin >> n;

    List list;
    Node** where = new Node*[n+1];

    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        Node* node = new Node{nullptr, i};
        where[i] = node;
        if(x == 0){
            pushFront(list, node);
        }
        else{
            insertAfter(where[x], node);
        }
    }

    for(Node* node = list.head; node != nullptr; node = node->next){
        cout << node->value;
        if(node->next != nullptr){
            cout << " ";
        }
    }

    delete[] where;

    return 0;
}