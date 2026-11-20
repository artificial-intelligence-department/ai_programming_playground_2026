#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template <typename T>
class DoubleList {
private:
    struct ListNode {
        T val = T();
        ListNode* next = nullptr;
        ListNode* prev = nullptr;
    };

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int size = 0;

public:
    DoubleList() = default;

    ~DoubleList() {
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    int getSize() const { return size; }

    T get(int index) const {
        ListNode* curr = nullptr;
        if (index >= size / 2) {
            curr = tail;
            for (int i = size - 1; i > index; i--) {
                curr = curr->prev;
            }
        } else {
            curr = head;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        return curr->val;
    }

    void set(int index, T val) {
        ListNode* curr = nullptr;
        if (index >= size / 2) {
            curr = tail;
            for (int i = size - 1; i > index; i--) {
                curr = curr->prev;
            }
        } else {
            curr = head;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        curr->val = val;
    }

    void insert(int n, int nOfInsrt) {
        if (nOfInsrt <= 0) return;
        size += nOfInsrt;

        if (head == nullptr) {
            ListNode* curr = nullptr;
            for (int i = 0; i < nOfInsrt; i++) {
                ListNode* New = new ListNode;
                cin >> New->val;
                New->prev = curr;
                if (i == 0) {
                    curr = New;
                    head = curr;
                    tail = curr;
                } else {
                    curr->next = New;
                    curr = New;
                    tail = curr;
                }
            }
        } 
        else if (n == 0) {
            ListNode* curr = head;
            for (int i = 0; i < nOfInsrt; i++) {
                ListNode* New = new ListNode;
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
            head = curr;
        } 
        else {
            ListNode* curr = head;
            for (int i = 0; i < n - 1; i++) {
                curr = curr->next;
            }
            ListNode* tmp = curr->next;

            for (int i = 0; i < nOfInsrt; i++) {
                ListNode* New = new ListNode;
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
                tail = curr;
            }
        }
    }

    void erase(int index, int nOfEls) {
        if (nOfEls <= 0 || head == nullptr) {
            return;
        }
        size -= nOfEls;
        ListNode* curr = head;

        if (index == 0) {
            for (int i = 0; i < nOfEls && curr != nullptr; i++) {
                ListNode* right = curr->next;
                delete curr;
                curr = right;
            }
            head = curr;
            if (curr == nullptr) {
                tail = nullptr;
            } else {
                curr->prev = nullptr;
            }
        } else {
            for (int i = 0; i < index - 1; i++) {
                curr = curr->next;
            }
            ListNode* right = curr->next;
            for (int i = 0; i < nOfEls && right != nullptr; i++) {
                ListNode* tmp = right;
                right = right->next;
                delete tmp;
            }
            curr->next = right;
            if (right == nullptr) {
                tail = curr;
            } else {
                right->prev = curr;
            }
        }
    }

    void print() const {
        cout << *this << endl;
    }

    friend ostream& operator<<(ostream& os, const DoubleList<T>& list) {
        ListNode* node = list.head;
        while (node != nullptr) {
            os << node->val;
            if (node->next != nullptr) os << " ";
            node = node->next;
        }
        return os;
    }
};

int main() {
    DoubleList<int> list;
    int menu = 0;
    cin >> menu;
    while (menu > 0) {
        string menu_option = "";
        cin >> menu_option;
        if (menu_option == "insert") {
            int n = 0, nOfInsrt = 0;
            cin >> n >> nOfInsrt;
            list.insert(n, nOfInsrt);
        } else if (menu_option == "erase") {
            int index = 0, nOfEls = 0;
            cin >> index >> nOfEls;
            list.erase(index, nOfEls);
        } else if (menu_option == "get") {
            int index = 0;
            cin >> index;
            cout << list.get(index) << endl;
        } else if (menu_option == "set") {
            int index = 0, val = 0;
            cin >> index >> val;
            list.set(index, val);
        } else if (menu_option == "print") {
            list.print();
        } else if (menu_option == "size") {
            cout << list.getSize() << endl;
        }
        menu--;
    }
    return 0;
}