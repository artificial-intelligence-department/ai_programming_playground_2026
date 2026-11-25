#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class Doublelist{
private:
struct Node{
    T data;
    Node *next;
    Node *prev;
    Node(T vall){
    data = vall;
    next = NULL;
    prev = NULL;
    }
};
    Node *head = NULL;
    Node *tail = NULL;
    Node *current = NULL;
    int size = 0;
public:
int getsize(){
    return size;
}
void getinsert(int index, int N, T *arr){
    if(N <= 0){
        return;
    }
    Node *newhead = NULL;
    Node *newtail = NULL;
    for(int i = 0; i < N; i++){
        Node *newNode = new Node(arr[i]);
        if(newhead == NULL){
            newhead = newNode;
            newtail = newNode;
        }
        else{
        newtail->next = newNode;
        newNode->prev = newtail;
        newtail = newNode;
        }
    }
    Node *p = getget(index);
    if(p == NULL){{
        if(head == NULL){
        head = newhead;
        tail = newtail;
        }
        else{
            tail->next = newhead;
            newhead->prev = tail;
            tail = newtail;
        }
    }
    }
    else if(p == head){
        newtail->next = head;
        head->prev = newtail;
        head = newhead;
    }
    else{
        Node *nodeb = p->prev;
        nodeb->next = newhead;
        newhead->prev = nodeb;
        newtail->next = p;
        p->prev = newtail;
    }
    size += N;
}
void geterase(int index, int N){
    if(N <= 0){
        return;
    }
    Node *start = getget(index);
    if(start == NULL){
        return;
    }
    Node *prevNode = start->prev;
    Node *current = start;
    for(int i = 0; i < N && current != NULL; i++){
        Node *newNode = current->next;
        delete current;
        current = newNode;
    }
    Node *endNode = current;
    if(prevNode == NULL){
        head = endNode;
    }
    else{
        prevNode->next = endNode;
    }
    if(endNode == NULL){
        tail = prevNode;
    }
    else{
        endNode->prev = prevNode;
    }
    size-= N;
}
Node *getget(int index){
    Node *current = head;
    for(int i = 0; i < index; i++){
        if(current == NULL){
            break;
        }
        current = current->next;
    }
    return current;
}
T get(int index){
    Node *now = getget(index);
    if(now == NULL){
        return T();
    }
    return now->data;
}
void getset(int index, T n){
    Node *point = getget(index);
    if(point != NULL){
        point->data = n;
    }
}
friend ostream& operator <<(ostream& os, const Doublelist &list){
    Node *current = list.head;
    while(current != NULL){
        os << current->data;
        current = current->next;
        os << " ";
    }
    return os;
}

};
int main(){
    Doublelist<int> List;
    int count = 0;
    cin >> count;
    char check[10];
    while(count > 0){
    cin >> check;
    if(strcmp(check, "insert")== 0){
        int index = 0;
        int n = 0;
        cin >> index >> n;
        int *arr = new int[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        List.getinsert(index, n, arr);
        delete[] arr;
    }
    else if(strcmp(check, "erase") == 0){
        int index = 0;
        int n = 0;
        cin >> index >> n;
        List.geterase(index, n);
    }
    else if(strcmp(check, "size") == 0){
        cout << List.getsize() << "\n";
    }
    else if(strcmp(check, "get") == 0){
        int index = 0;
        cin >> index;
        cout << List.get(index) << "\n";
    }
    else if(strcmp(check, "set") == 0){
        int index = 0;
        int nov = 0;
        cin >> index >> nov;
        List.getset(index, nov);
    }
    else if(strcmp(check, "print") == 0){
        cout << List << "\n";
    }
    count--;
}
return 0;
}