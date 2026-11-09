#include <iostream>
#include <iomanip>

using namespace std;

struct ListNode{
    ListNode *next = nullptr;
    int val = 0;
};

struct List{
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int size = 0;
};

void print(List *list){
    if(list->size == 0 ){
        cout<<"list's empty\n";
        return;
    }
    ListNode *curr = list->head;
    do{
        cout << curr->val <<" ";
        curr = curr->next;
    }while(curr != nullptr);
    cout << endl;
}

bool valid(){
    if(cin.fail()){
        cin.ignore(1000000, '\n');
        cin.clear();
        cout <<"Err: incorrect input\n";
        return false;
    }
    return true;
}

void insert( List *&list){
    cout << "enter val to append\n";
    int val = 0;
    cin >> val;
    if(!valid()){
        cout << "invalid input\n";
        return;
    }
    cout <<"enter pos to insrt\n";
    int n = 0;
    cin >> n;
    if(!valid()){
        cout << "invalid input\n";
        return;
    }
    
    if(n > list->size + 1|| n <= 0 ){
        cout << "invalid input\n";
        return;
    }
    ListNode *curr = new ListNode;
    curr->val = val;
    if(list->size == 0){
        list->head = curr;
        list->tail = curr;
        list->size++;
        cout <<"Inserted\n";
        print(list);
        return;
    }
    curr->next = list->head;
    if(n==1){
        list->head = curr;
        list->size++;
        cout <<"Inserted\n";
        print(list);
        return;
    }
    ListNode *tmp = list->head;
    for(int i = 1; i < n -1; i++){
        tmp = tmp->next;
    }
    curr->next = tmp->next;
    tmp->next = curr;
    list->size++;
    if(n == list->size){
        curr->next = nullptr;
        list->tail = curr;
    }
    cout <<"Inserted\n";
    print(list);

    
}

void del_el(List *&list){
    cout << "enter number of el to delete\n";
    int n = 0;
    cin >> n;
    if(!valid()){
        cout << "invalid input\n";
        return;
    }
    if(n > list->size || n <= 0 ){
        cout << "invalid input\n";
        return;
    }
    if(list->size == 1){
        list->size = 0;
        delete list->head;
        list->head = nullptr;
        list->tail = nullptr;
        cout << "deleted succesfully\n";
        print(list);
        return;
    }
    ListNode *curr = list->head;
    if(n==1){
        list->head = curr->next;
        delete curr;
        list->size--;
        return;
    }
    for(int i = 1; i < n -1; i++){
        curr = curr->next;
    }
    ListNode *tmp = curr->next;
    curr->next = tmp->next;
    delete tmp;
    if(n == list->size){
        list->tail = curr;
    }
    list->size --;
    cout << "deleted succesfully\n";
    print(list);
}

void destroyList(List *&list) {
    if(!list){
    cout << "nothing to destroy\n";
    return;
    } 
    ListNode *curr = list->head;
    while (curr != nullptr) {
        ListNode *nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    delete list;
    list = nullptr;
    cout << "destroyed succesfully\n";
}

int main(){
    List *list = new List;
    int menu_option = -1;
    do{
        cout <<"         Menu:\nAdd val to list = 1\nDel el number *up to your choice* from list = 2\nExit = 0\n";
        cin >> menu_option;
        if(!valid()){
            cout << "Invalid option. try again\n";
            continue;
        }
        if(menu_option < 0 || menu_option > 2){
            cout << "Invalid option. try again\n";
            continue;
        }
        switch (menu_option)
        {
        case 1:
            insert(list);
            break;
        case 2:
            del_el(list);
             break;
        default:
            break;
        }
    }while(menu_option != 0);
    destroyList(list);
}
