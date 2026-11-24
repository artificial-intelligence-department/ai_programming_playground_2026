// Всеукраїнська олімпіада

#include <iostream>
using namespace std;

template<typename T>
struct Stack {
    struct Node {
        T data;
        Node* next;
        Node (T d, Node* n = nullptr) {
            data=d;
            next = n;
        }

    };

    Node* top = nullptr;
    int count = 0;

    bool empty() {
        return (count==0);
    }

    int size() {
        return count;
    }

    void push(T d) {
        top = new Node(d, top);
        count++;
    }

    T pop() {
        Node* tmp = top;
        top = top->next;
        T c = tmp->data;
        delete tmp;
        
        return c;
    }

    ~Stack() {
        while (top!=nullptr) {
            pop();
        }
    }


};

struct Array {
    struct Point {
        int l;
        int r;
        Point() = default;
        Point(int left, int right) {
            l=left;
            r=right;
        }
    };
    int capacity=1;
    int count=0;
    Point* arr = new Point[capacity];

    void push(Point r) {
        if (count >=capacity) {
            capacity*=2;
            Point* array = new Point[capacity];
            for (int i =0; i<count; i++) {
                array[i]=arr[i];
            }
            delete[] arr;
            arr = array;
        }
        arr[count] = r;
        count++;
    }

    int size() {
        return count;
    }

    void printCoord() {
        for (int i =0; i<count; i++) {
            cout << arr[i].l << " " << arr[i].r << endl;
        }
    }

    ~Array() {
        delete[] arr;
    }

};

int main() {
    string s;
    cin >> s;
    Stack<int> stack;
    Array arr;
    for (int i=0; i<s.size(); i++) {
        if (s[i]=='(') {
            stack.push(i+1);
        }
        if(s[i]==')') {
            arr.push({stack.pop(), i+1});
        }
    }
    cout << arr.size() << endl;
    arr.printCoord();
}