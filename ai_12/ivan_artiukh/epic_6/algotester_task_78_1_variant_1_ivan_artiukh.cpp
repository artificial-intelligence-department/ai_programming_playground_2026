#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct ListNode {
    ListNode *next = nullptr;
    ListNode *prev = nullptr;
    int val = 0;
};

struct List {
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int size = 0;
};

ostream& operator<<(ostream& os, List *list) {
    ListNode *node = list->head;
    while (node != nullptr) {
        os << node->val;
        if (node->next != nullptr) os << " ";
        node = node->next;
    }
    return os;
}

void print(List *list) {
    cout << list << endl;
}

void insert(List *&list) {
    int n = 0;
    cin >> n;
    int nOfInsrt = 0;
    cin >> nOfInsrt;

    if (nOfInsrt <= 0) return;
    list->size += nOfInsrt;

    if (list->head == nullptr) {
        ListNode *curr = nullptr;
        for (int i = 0; i < nOfInsrt; i++) {
            ListNode *New = new ListNode;
            cin >> New->val;
            New->prev = curr;
            if (i == 0) {
                curr = New;
                list->head = curr;
                list->tail = curr;
            } else {
                curr->next = New;
                curr = New;
                list->tail = curr;
            }
        }
    } 
    else if (n == 0) {
        ListNode *curr = list->head;
        for (int i = 0; i < nOfInsrt; i++) {
            ListNode *New = new ListNode;
            cin >> New->val;
            New->next = curr;
            New->prev = curr->prev;
            if (curr->prev != nullptr) {
                curr->prev->next = New;
            }
            curr->prev = New;
        }
        while (curr->prev != nullptr) {
            curr = curr->prev;
        }
        list->head = curr;
    } 
    else {
        ListNode *curr = list->head;
        for (int i = 0; i < n - 1; i++) {
            curr = curr->next;
        }
        ListNode *tmp = curr->next;

        for (int i = 0; i < nOfInsrt; i++) {
            ListNode *New = new ListNode;
            cin >> New->val;
            New->next = tmp;
            New->prev = curr;
            curr->next = New;
            if (tmp != nullptr) {
                tmp->prev = New;
            }
            curr = New;
        }
        if (tmp == nullptr) {
            list->tail = curr;
        }
    }
}

void del_el(List *&list) {
    int index = 0;
    cin >> index;
    int nOfEls = 0;
    cin >> nOfEls;
    if (nOfEls <= 0 || list->head == nullptr) {
        return;
    }
    list->size -= nOfEls;
    ListNode *curr = list->head;

    if (index == 0) {
        for (int i = 0; i < nOfEls && curr != nullptr; i++) {
            ListNode *right = curr->next;
            delete curr;
            curr = right;
        }
        list->head = curr;
        if (curr == nullptr) {
            list->tail = nullptr;
        } else {
            curr->prev = nullptr;
        }
    } else {
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        ListNode *right = curr->next;
        for (int i = 0; i < nOfEls && right != nullptr; i++) {
            ListNode *tmp = right;
            right = right->next;
            delete tmp;
        }
        curr->next = right;
        if (right == nullptr) {
            list->tail = curr;
        } else {
            right->prev = curr;
        }
    }
}

void get(List *list) {
    int index = 0;
    cin >> index;
    ListNode *curr = nullptr;
    if (index >= list->size / 2) {
        curr = list->tail;
        for (int i = list->size - 1; i > index; i--) {
            curr = curr->prev;
        }
    } else {
        curr = list->head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
    }
    cout << curr->val << endl;
}

void set(List *list) {
    int index = 0;
    cin >> index;
    int val = 0;
    cin >> val;
    ListNode *curr = nullptr;
    if (index >= list->size / 2) {
        curr = list->tail;
        for (int i = list->size - 1; i > index; i--) {
            curr = curr->prev;
        }
    } else {
        curr = list->head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
    }
    curr->val = val;
}

void destroyList(List *&list) {
    if (list == nullptr) return;
    ListNode *curr = list->head;
    while (curr != nullptr) {
        ListNode *nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    delete list;
    list = nullptr;
}

int main() {
    List *list = new List; 
    int menu = 0;
    cin >> menu;
    while (menu > 0) {
        string menu_option = "";
        cin >> menu_option;
        if (menu_option == "insert") {
            insert(list);
        } else if (menu_option == "erase") { 
            del_el(list);
        } else if (menu_option == "get") {
            get(list);
        } else if (menu_option == "set") {
            set(list);
        } else if (menu_option == "print") {
            print(list);
        } else if (menu_option == "size") {
            cout << list->size << endl;
        }
        menu--;
    }
    destroyList(list);
    return 0;
}
