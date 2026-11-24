#include <iostream>
#include <iomanip>

using namespace std;

struct Node{
    int value;
    Node* next;
    Node* prev;
};

struct DblLinkedList{
    size_t size;
    Node *head;
    Node *tail;   
};

DblLinkedList* createDblLinkedList(int data){
    Node *newHead = new Node{data, nullptr, nullptr};
    newHead->next = newHead;
    newHead->prev = newHead;
    DblLinkedList *newList = new DblLinkedList{1, newHead, newHead};
    return newList;
}

void deleteDblLinkderList(DblLinkedList* list){
    if (list==nullptr) return;
    Node *currentNode = list->head;
    while (currentNode) {
        delete currentNode->prev; 
        currentNode = currentNode->next;
    }
    delete list;
}

void pushFront(DblLinkedList *list, int data){
    Node* newNode = new Node{data, list->head, list->tail};
    list->head->prev = newNode;
    list->tail->next = newNode;
    list->head = newNode;
    list->size++;
}

void pushBack(DblLinkedList *list, int data){
    Node* newNode = new Node{data, list->head, list->tail};
    list->head->prev = newNode;
    list->tail->next = newNode;
    list->tail = newNode;
    list->size++;
}

void popFront(DblLinkedList *list){
    if (list->size == 0) return;
    list->tail->next = list->head->next;
    list->head->next->prev = list->tail;
    Node* temp = list->head;
    list->head = list->head->next;
    delete temp;
    list->size--;
}

void popBack(DblLinkedList *list){
    if (list->size == 0) return;
    list->tail->prev->next = list->head;
    list->head->prev = list->tail->prev;
    Node* temp = list->tail;
    list->tail = list->tail->prev;
    delete temp;
    list->size--;
}

void printDblLinkedList(DblLinkedList *list){
    Node *current = list->head;
    while (current!=list->tail){
        cout << current->value << " -> ";
        current = current->next;
    }
    cout << current->value << "\n";
}

int main(){
    DblLinkedList myList = *createDblLinkedList(15);
    cout << "step 1: ";
    printDblLinkedList(&myList);
    
    pushFront(&myList, 14);
    pushBack(&myList, 16);
    cout << "step 2: ";
    printDblLinkedList(&myList);
    
    popFront(&myList);
    cout << "delete first element:\nstep 3: ";
    printDblLinkedList(&myList);

    pushBack(&myList, 17);
    cout << "add element back:\nstep 4: ";
    printDblLinkedList(&myList);

    return 0;
}