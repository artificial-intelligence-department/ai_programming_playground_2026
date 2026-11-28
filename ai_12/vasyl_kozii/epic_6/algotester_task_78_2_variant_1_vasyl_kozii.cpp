/*
Algotester Task 78 2 Variant 1
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};
template <typename T>
struct DoublyLinkedList {
    Node<T>* head;
    Node<T>* tail;
    int sz;
    DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}
    int size() {
        return sz;
    }
    Node<T>* getNode(int index) {
        if(index<0 || index>=sz) return nullptr;
        Node<T>* curr;
        if(index<sz/2) {
            curr=head;
            for(int i=0; i<index; i++) {
                curr=curr->next;
            }
        } else {
            curr=tail;
            for(int i=sz-1; i>index; i--) {
                curr=curr->prev;
            }
        }
        return curr;
    }
    void insert(int index, int n, T* arr) {
        if(n<=0) return;
        if(index<0 || index>sz) return;
        for(int i=0; i<n; i++) {
            int targetIdx=index+i;
            Node<T>* newNode=new Node<T>(arr[i]);
            if(sz==0) {
                head=tail=newNode;
            } else if(targetIdx==0) {
                newNode->next=head;
                head->prev=newNode;
                head=newNode;
            } else if(targetIdx>=sz) {
                tail->next=newNode;
                newNode->prev=tail;
                tail=newNode;
            } else {
                Node<T>* curr=getNode(targetIdx);
                Node<T>* p=curr->prev;
                p->next=newNode;
                newNode->prev=p;
                newNode->next=curr;
                curr->prev=newNode;
            }
            sz++;
        }
    }
    void erase(int index, int n) {
        if(n<=0 || index<0 || index>=sz) return;
        int count=0;
        while(count<n && index<sz) {
            Node<T>* target=getNode(index);
            if(!target) break;
            Node<T>* p=target->prev;
            Node<T>* nxt=target->next;
            if(target==head) {
                head=nxt;
            }
            if(target==tail) {
                tail=p;
            }
            if(p) p->next=nxt;
            if(nxt) nxt->prev=p;
            delete target;
            sz--;
            count++;
        }
    }
    T get(int index) {
        Node<T>* node=getNode(index);
        if(node) return node->data;
        return T();
    }
    void set(int index, T val) {
        Node<T>* node=getNode(index);
        if(node) node->data=val;
    }
    friend ostream& operator<<(ostream& os, const DoublyLinkedList<T>& list) {
        Node<T>* curr=list.head;
        while(curr) {
            os<<curr->data;
            if(curr->next) os<<" ";
            curr=curr->next;
        }
        return os;
    }
    ~DoublyLinkedList() {
        Node<T>* curr=head;
        while(curr) {
            Node<T>* nextNode=curr->next;
            delete curr;
            curr=nextNode;
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    if(!(cin>>q)) return 0;
    DoublyLinkedList<int> list;
    while(q--) {
        string cmd;
        cin>>cmd;
        if(cmd=="insert") {
            int index, n;
            cin>>index>>n;
            int* arr=new int[n];
            for(int i=0; i<n; i++) {
                cin>>arr[i];
            }
            list.insert(index, n, arr);
            delete[] arr;
        } else if(cmd=="erase") {
            int index, n;
            cin>>index>>n;
            list.erase(index, n);
        } else if(cmd=="size") {
            cout<<list.size()<<"\n";
        } else if(cmd=="get") {
            int index;
            cin>>index;
            cout<<list.get(index)<<"\n";
        } else if(cmd=="set") {
            int index, val;
            cin>>index>>val;
            list.set(index, val);
        } else if(cmd=="print") {
            cout<<list<<"\n";
        }
    }
}