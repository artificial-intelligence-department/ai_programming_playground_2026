#include <iostream>
#include <string>

using namespace std;

struct Masiv {
    int size = 0;
    int capacity = 1;
    int* mas = new int[capacity];
};

void Size(const Masiv& m) {
    cout << m.size << endl;
}

void Capacity(const Masiv& m) {
    cout << m.capacity << endl;
}

int* Resize(Masiv& m) {
    m.capacity *= 2;
    int* tmp = new int[m.capacity];
    for (int i = 0; i < m.size; i++) {
        tmp[i] = m.mas[i];
    }
    return tmp;
}

void Insert(Masiv& m, int index, int num) {
    for (int i = m.size - 1; i >= index; i--) {
        m.mas[i + 1] = m.mas[i];
    }
    m.mas[index] = num;
    m.size++;
    if (m.size == m.capacity) {
        int* tmp = Resize(m);
        delete[] m.mas;
        m.mas = tmp;
    }
}

void Erase(Masiv& m, int index, int count) {
    for (int i = 0; i < count; i++) {
        m.mas[index + i] = 0;
    }
    for (int i = index + count; i < m.size; i++) {
        m.mas[i - count] = m.mas[i];
    }
    m.size -= count;
}

void Print(const Masiv& m) {
    for (int i = 0; i < m.size; i++) {
        cout << m.mas[i] << " ";
    }
    cout << endl;
}

void Get(const Masiv& m, int index) {
    cout << m.mas[index] << endl;
}

void Set(Masiv& m, int index, int number) {
    m.mas[index] = number;
}

void Delete(Masiv& m) {
    delete[] m.mas;
    m.mas = nullptr;
}

int main() {
    int n;
    string action;
    cin >> n;
    Masiv mas;

    for (int i = 0; i < n; i++) {
        cin >> action;
        if (action == "insert") {
            int a, b, num;
            cin >> a >> b;
            for (int j = 0; j < b; j++) {
                cin >> num;
                Insert(mas, a, num);
                a++;
            }
        }
        else if (action == "erase") {
            int a, b;
            cin >> a >> b;
            Erase(mas, a, b);
        }
        else if (action == "size") {
            Size(mas);
        }
        else if (action == "capacity") {
            Capacity(mas);
        }
        else if (action == "get") {
            int a;
            cin >> a;
            Get(mas, a);
        }
        else if (action == "set") {
            int a, b;
            cin >> a >> b;
            Set(mas, a, b);
        }
        else if (action == "print") {
            Print(mas);
        }
    }

    Delete(mas);

    return 0;
}