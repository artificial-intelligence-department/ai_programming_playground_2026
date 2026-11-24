#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    char* data;
    Node* prev;
    Node* next;
};

struct DoubleLinkedList {
    size_t size;
    Node *HEAD;
    Node *TAIL;
};

DoubleLinkedList* createDoubleLinkedList() {
    DoubleLinkedList *tmp = new DoubleLinkedList;
    tmp->size=0;
    tmp->HEAD=nullptr;
    tmp->TAIL=nullptr;
    return tmp;
}

void deleteDoubleLinkedList(DoubleLinkedList** list) {
    if (list==nullptr || *list == nullptr) {
        return;
    }
    Node *tmp = (*list)->HEAD;
    Node *next = nullptr;
    while (tmp) {
        next = tmp->next;
        delete[] tmp->data;
        delete tmp;
        tmp = next;
    }
    delete (*list);
    *list = nullptr;
}

void pushFront(DoubleLinkedList *list, char* data) {
    if (list == nullptr) {
        cout << "Порожній вказівник на список"<< endl;
        return;
    }
    Node *tmp = new Node;
    tmp->data = data;
    tmp->prev = nullptr;
    tmp->next=list->HEAD;
    if(list->HEAD) {
        list->HEAD->prev=tmp;
    }
    list->HEAD=tmp;
    if(list->TAIL==nullptr) {
        list->TAIL=tmp;
    }
    list->size++;
}

char* popFront (DoubleLinkedList *list) {
    if (list == nullptr) {
        cout << "Порожній вказівник на список"<< endl;
        return nullptr;
    }
    if(list->HEAD==nullptr) {
        cout << "Помилка! У списку немає елементів."<<endl;
        return nullptr;
    } 
    Node* temp = list->HEAD;
    Node* next = list->HEAD->next;
    if (next) {
        next->prev=nullptr;
        list->HEAD=next;
        
    } else {
        list->HEAD=nullptr;
        list->TAIL=nullptr;

    }
    char* deleteddata = temp->data;
    delete temp;
    list->size--;
    return deleteddata;

}

void pushBack(DoubleLinkedList *list, char* data) {
    if (list == nullptr) {
        cout << "Порожній вказівник на список"<< endl;
        return;
    }
    Node *tmp = new Node;
    tmp->data = data;
    tmp->prev = list->TAIL;
    tmp->next=nullptr;
    if(list->TAIL) {
        list->TAIL->next=tmp;
    }
    list->TAIL=tmp;
    if(list->HEAD==nullptr) {
        list->HEAD=tmp;
    }
    list->size++;
}

char* popBack (DoubleLinkedList *list) {
    if (list == nullptr) {
        cout << "Порожній вказівник на список"<< endl;
        return nullptr;
    }
    if(list->HEAD==nullptr) {
        cout << "Помилка! У списку немає елементів."<<endl;
        return nullptr;
    } 
    Node* temp = list->TAIL;
    Node* prev = list->TAIL->prev;
    if (prev) {
        prev->next=nullptr;
        list->TAIL=prev;
        
    } else {
        list->HEAD=nullptr;
        list->TAIL=nullptr;

    }
    char* deleteddata = temp->data;
    delete temp;
    list->size--;
    return deleteddata;

}

Node* getElement(DoubleLinkedList *list, size_t index) {
    if (list == nullptr) {
        cout << "Порожній вказівник на список"<< endl;
        return nullptr;
    }
    if(list->HEAD==nullptr) {
        cout << "Помилка! У списку немає елементів."<<endl;
        return nullptr;
    } 
    if (index >= list->size) {
        cout << "Помилка! Вихід за межі списку."<< endl;
        return nullptr;
    }
    Node* temp = list->HEAD;
    size_t i=0;
    while (temp && i<index) {
        temp=temp->next;
        i++;
    }
    return temp;
}

void insertBefore(DoubleLinkedList *list, size_t index, char* value) {
    Node *element=getElement(list, index);
    if (element == nullptr) {
        return;
    }
    Node* insertion = new Node;
    insertion->data=value;
    insertion->next=element;
    insertion->prev=element->prev;
    if (insertion->prev!=nullptr) {
        insertion->prev->next=insertion;
    } else {
        list->HEAD=insertion;
    }

    element->prev=insertion;
    list->size++;
    
}

void deleteElement(DoubleLinkedList *list, size_t n) {
    Node* element = getElement(list, n);
    if (element == nullptr) {
        return;
    }
    if(element->next!=nullptr && element->prev!=nullptr) {
        element->prev->next=element->next;
        element->next->prev=element->prev;
    } else if(element->next==nullptr && element->prev!= nullptr) {
        list->TAIL = element->prev;
        element->prev->next=nullptr;
    } else if(element->next!=nullptr && element->prev== nullptr) {
        list->HEAD=element->next;
        element->next->prev=nullptr;     
    } else {
        list->HEAD=nullptr;
        list->TAIL=nullptr;
    }
    delete[] element->data;
    delete element;
    list->size--;
}

void listPrint(DoubleLinkedList *list) {
    Node* temp;
    if(list==nullptr || list->HEAD==nullptr) {
        cout << "Список пустий." << endl;
        return;
    }
    else {
        temp = list->HEAD;
        do {
            cout<< temp->data << " ";
            temp=temp->next;

        } while (temp!=nullptr);
        cout << endl;
    }
}

int findIndexByKey(DoubleLinkedList *list, const char *key) {
    if(list==nullptr || list->HEAD==nullptr) {
        return -1;
    }
    Node* temp=list->HEAD;
    int index=0;
    while(temp!=nullptr) {
        if(strcmp(temp->data, key)==0) {
            return index;
        }
        temp=temp->next;
        index++;
    }
    return -1;
}


int main() {
    DoubleLinkedList *list = createDoubleLinkedList();
    int N;
    cout << "Введіть початкову кількість елементів: ";
    cin >> N;
    cin.ignore(10000, '\n');
    for (int i = 0; i<N; i++) {
        char* data = new char[32];
        cin.getline(data, 32);
        pushBack(list, data);

    }
    cout << "--- List ---"<< endl;
    listPrint(list);
    cout << "Введіть елемент, який потрібно знищити: "<<endl;
    char* find = new char[32];
    cin.getline(find, 32);
    int find_index = findIndexByKey(list, find);
    if (find_index==-1) {
        cout << "Не знайдено такий елемент." << endl;
        delete[] find;
        deleteDoubleLinkedList(&list);
        return 1;
    } else {
        deleteElement(list, find_index);
    }
    
    cout << "--- List ---"<< endl;
    listPrint(list);
    cout << "Введіть перед яким елементом хочете вставити інші елементи:" << endl;
    cin.getline(find, 32);
    find_index = findIndexByKey(list, find);
    if (find_index==-1) {
        cout << "Не знайдено такий елемент." << endl;
        delete[] find;
        deleteDoubleLinkedList(&list);
        return 1;
    } else {
        int n;
        cout <<"Введіть кількість елементів, які потрібно додати: ";
        cin >> n;
        cin.ignore(10000, '\n');
        for (int i =0; i<n; i++) {
            char* data=new char[32];
            cin.getline(data, 32);
            find_index=findIndexByKey(list, find);
            insertBefore(list, find_index, data);
            find_index++;
            
        }
    }
    
    delete[] find;
    find=nullptr;

    cout << "--- List ---"<< endl;
    listPrint(list);

    deleteDoubleLinkedList(&list);
    return 0;






}