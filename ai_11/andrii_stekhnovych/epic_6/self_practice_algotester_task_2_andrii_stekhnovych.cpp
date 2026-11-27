// Cупер карти

#include <iostream>
using namespace std;

template<typename T>
struct Queue {
    struct Node {
        T data;
        Node* next;
        Node(T d, Node* n = nullptr) {
            data=d;
            next = n;
        }
    };

    int count=0;
    Node* head = nullptr;
    Node* tail = nullptr;


    bool empty() {
        return (count==0);
    }

    int size() {
        return count;
    }

    void push(T v) {
        Node* tmp = new Node(v);
        if(empty()) {
            head = tmp;
            tail=tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
        count++;

    }

    void pop() {
        if(empty()) {
            return;
        }
        Node* temp = head;
        head=head->next;
        if(!head) {
            tail = nullptr;
        }
        delete temp;
        count--;
        
    }

    T& front() {
        return head->data;
    } 

};

int main() {
    int n;
    cin >> n;
    Queue<int> q;
    for (int i=1; i<=n; i++) {
        q.push(i);
    }
    while (q.size()>1) {
        q.pop();
        int next = q.front();
        q.pop();
        q.push(next);
    }
    cout << q.front();
    return 0;

    
}