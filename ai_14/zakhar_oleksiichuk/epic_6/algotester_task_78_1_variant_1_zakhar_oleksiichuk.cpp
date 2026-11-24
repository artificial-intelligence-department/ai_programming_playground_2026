#include <iostream>
#include <string>

using namespace std;

struct DoublyLinkedList
{
    struct Node
    {
        int key;
        Node *next;
        Node *prev;
    };

    Node *head = nullptr;
    Node *tail = nullptr;

    ~DoublyLinkedList()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    int size() const
    {
        int count = 0;
        for (Node *curr = head; curr != nullptr; curr = curr->next)
            count++;
        return count;
    }

    friend ostream &operator<<(ostream &out, const DoublyLinkedList &list)
    {
        for (Node *curr = list.head; curr != nullptr; curr = curr->next)
            out << curr->key << " ";
        return out;
    }

    void insert(int index, int n)
    {
        if (n == 0)
            return;
        Node *newHead = nullptr;
        Node *newTail = nullptr;
        int lSize = size();

        for (int i = 0; i < n; i++)
        {
            int value;
            cin >> value;

            Node *newNode = new Node{value, nullptr, nullptr};
            if (newHead == nullptr)
            {
                newHead = newTail = newNode;
            }
            else
            {
                newTail->next = newNode;
                newNode->prev = newTail;
                newTail = newNode;
            }
        }

        if (head == nullptr)
        {
            head = newHead;
            tail = newTail;
        }
        else if (index == 0)
        {
            newTail->next = head;
            head->prev = newTail;
            head = newHead;
        }
        else if (index == lSize)
        {
            tail->next = newHead;
            newHead->prev = tail;
            tail = newTail;
        }
        else
        {
            Node *curr = head;
            for (int i = 0; i < index - 1; i++)
                curr = curr->next;

            Node *currNext = curr->next;
            curr->next = newHead;
            newHead->prev = curr;
            currNext->prev = newTail;
            newTail->next = currNext;
        }
    }

    void erase(int index, int n)
    {
        if (n == 0 || head == nullptr)
            return;

        Node *curr = head;
        for (int i = 0; i < index; i++)
            curr = curr->next;

        Node *before = curr->prev;
        for (int i = 0; i < n && curr != nullptr; i++)
        {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }

        if (before != nullptr)
            before->next = curr;
        else
            head = curr;

        if (curr != nullptr)
            curr->prev = before;
        else
            tail = before;
    }

    int get(int index)
    {
        Node *curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        if (curr != nullptr)
            return curr->key;
        throw out_of_range("Вихід за межі");
    }

    void set(int index, int value)
    {
        Node *curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            curr->key = value;
            return;
        }
        throw out_of_range("Вихід за межі");
    }
};

int main()
{
    int Q;
    cin >> Q;

    DoublyLinkedList list;
    string command;

    int index, n;

    while (Q--)
    {
        cin >> command;

        if (command == "insert")
        {
            cin >> index >> n;
            list.insert(index, n);
        }
        else if (command == "erase")
        {
            cin >> index >> n;
            list.erase(index, n);
        }
        else if (command == "size")
        {
            cout << list.size() << endl;
        }
        else if (command == "get")
        {
            cin >> index;
            cout << list.get(index) << endl;
        }
        else if (command == "set")
        {
            cin >> index >> n;
            list.set(index, n);
        }
        else if (command == "print")
        {
            cout << list << endl;
        }
    }
}