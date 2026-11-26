#include <iostream>
using namespace std;

struct Node{
    int key;
    Node* previous;
    Node* next;    
};
struct List{
    Node* head;
    Node* tail;
    int size_of_list;
};
List* createList(int elements){
    List* myList = new List;
    myList->head = nullptr;
    myList->tail= nullptr;
    myList->size_of_list=0;
    
    int val;
    cin>>val;
    Node* newNode = new Node;
    newNode->key=val;
    newNode->previous=nullptr; 
    newNode->next=nullptr;
    myList->head=newNode;
    myList->tail=newNode;
    myList->size_of_list++;


    for(int i =1; i<=elements-1; i++){
        cin>>val;
        Node* newNode = new Node;
        newNode->key=val;
        newNode->previous=myList->tail; 
        newNode->next=nullptr;
        myList->tail->next=newNode;
        myList->tail=newNode;
        myList->size_of_list++;
    }
    return myList;
}
void printList(List* myList){
    if(myList->head==nullptr){
        cout<<"Список порожній\n";
        return;
    }
    Node* tmp = myList->head;
    cout<<"Поточний список:\n";
    while(tmp!=nullptr){
        cout<<tmp->key<<" ";
        tmp=tmp->next;
    }
    cout<<"\n";
}
void deleteElements(int n, int K, List *&myList){
    if (myList->head == nullptr){
        cout<<"Список порожній\n";
        return;
    }

    Node* tmp = myList->head;
    Node* next_to_delete = nullptr;

    int i =0;
    while (tmp && i<n){
        tmp = tmp->next;
        i++;
    }

    next_to_delete=tmp->previous;

    if(K<=i){
        for(int j =1; j<=K; j++){
            Node* prev_el=next_to_delete->previous;
            delete next_to_delete;
            next_to_delete=prev_el;
            myList->size_of_list--;
        }
        tmp->previous = next_to_delete;
        if (next_to_delete != nullptr){
            next_to_delete->next = tmp;
        } else {
            myList->head = tmp;
        }
    }else{
        while(next_to_delete!=nullptr){
            Node* prev_el=next_to_delete->previous;
            delete next_to_delete;
            next_to_delete=prev_el;
            myList->size_of_list--;
        }
        tmp->previous = nullptr;
        myList->head = tmp;
    }
    
}
bool validInput(){
    if(cin.fail()){
        cin.ignore(10000, '\n');
        cin.clear();
        return false;
    }
    return true;
    
}
void insertOneElement(int val, List* &myList ){
    Node* newNode = new Node;
    newNode->key=val;
    newNode->next=nullptr;
    if(myList->head==nullptr){
        newNode->previous=nullptr;
        myList->head=newNode;
        myList->tail=newNode;
    }else{
        newNode->previous=myList->tail;
        myList->tail->next=newNode;
        myList->tail=newNode; 
    }
    
    myList->size_of_list++;

}
void insertElements(int A, List* &myList){
    cout<<"Введіть елементи через пробіл:\n";
    for (int i = 0; i<A; i++){
        int val;
        cin>>val;
        if(!validInput()){
            cout<<"Помилка. Значення мають бути цілими числами.\n";
            return;
        }
        insertOneElement(val,myList);
     }
}
void deleteList(List *&myList){
    Node* tmp = myList->head;
    while(tmp!=nullptr){
        Node* next_to_delete = tmp->next;
        delete tmp;
        tmp = next_to_delete;
    }
    delete myList;
    myList = nullptr;
}

int main(){
    int elements;
    while(true){
        cout<<"Введіть кількість елементів списку: \n";
        cin>>elements;
        if(validInput() && elements>=1) break;
    }

    cout<<"Введіть елементи списку через пробіл: \n";
    List* myList = createList(elements);
    printList(myList);
    int choice=-1;
    do{
        cout<<"Меню\n1 Знищити K елементів перед n елементом\n2 Записати нові К значень в кінець списка\n0 Закінчити програму\n";
        cin>>choice;
        if(!validInput()) continue;   
        switch(choice){
        case 1:   
            int n, K;
            cout<<"Введіть індекс елемента: \n";
            cin>>n;
            cout<<"Введіть кількість елементів для видалення:\n";
            cin>>K;
            if(!validInput() || n<1 || n>=myList->size_of_list|| K<1){
                cout<<"Помилка. Очікується цілі числа n >= 1 та менше за довжину списку та К>=1.\n";
                break;
            }
            deleteElements(n, K, myList);
            printList(myList);
            break;
        case 2:
            cout<<"Введіть кількість елементів для вставлення: \n";
            int A;
            cin>>A;
            if(!validInput() || A<1){
                cout<<"Помилка. Очікується ціле число від 1.\n";
                break;
            }
            insertElements(A, myList);
            printList(myList);
            break;
        case 0:
            deleteList(myList);
            break;
        default:
            break;    
        }

   }while(choice!=0);
}