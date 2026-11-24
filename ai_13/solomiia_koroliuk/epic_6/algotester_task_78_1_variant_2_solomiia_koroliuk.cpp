#include <iostream>
#include <cstring>
using namespace std;

struct DynArray {
    int *data;
    int sz;
    int cap;

    DynArray() : data(new int[1]), sz(0), cap(1) {} // Конструктор за замовчуванням: виділяє пам'ять під 1 елемент, поточний розмір = 0, місткість = 1
    ~DynArray() { delete[] data; } // Деструктор: звільняє динамічно виділену пам'ять при знищенні об'єкта
    DynArray(const DynArray &) = delete; // забороняємо копіювання
    DynArray &operator=(const DynArray &) = delete; // забороняємо присвоєння

    // збільшуємо ємність вдвічі, поки не вміститься need елементів
    void grow(int need) {
        int newCap = cap;
        while (need >= newCap) newCap *= 2;
        if (newCap == cap) return;
        int *p = new int[newCap];
        for (int i = 0; i < sz; i++) p[i] = data[i];
        delete[] data;
        data = p;
        cap = newCap;
    }

    // вставка n елементів з arr на позицію index
    void insert(int index, int n, const int *arr) {
        grow(sz + n);
        for (int i = sz - 1; i >= index; i--) data[i + n] = data[i];
        for (int i = 0; i < n; i++) data[index + i] = arr[i];
        sz += n;
    }

    // видалення n елементів, починаючи з index
    void erase(int index, int n) {
        for (int i = index + n; i < sz; i++) data[i - n] = data[i];
        sz -= n;
    }

    int &operator[](int i) { return data[i]; }
};

ostream &operator<<(ostream &os, const DynArray &a) {
    for (int i = 0; i < a.sz; i++) {
        if (i > 0) os << ' ';
        os << a.data[i];
    }
    return os;
}

int main() {
    DynArray a;
    int q;
    cin >> q;

    while (q--) {
        char cmd[16];
        cin >> cmd;

        if (strcmp(cmd, "insert") == 0) {
            int index, n;
            cin >> index >> n;
            int *tmp = new int[n];
            for (int i = 0; i < n; i++) cin >> tmp[i];
            a.insert(index, n, tmp);
            delete[] tmp;
        } else if (strcmp(cmd, "erase") == 0) {
            int index, n;
            cin >> index >> n;
            a.erase(index, n);
        } else if (strcmp(cmd, "size") == 0) {
            cout << a.sz << "\n\n";
        } else if (strcmp(cmd, "capacity") == 0) {
            cout << a.cap << "\n\n";
        } else if (strcmp(cmd, "get") == 0) {
            int index;
            cin >> index;
            cout << a[index] << "\n\n";
        } else if (strcmp(cmd, "set") == 0) {
            int index, v;
            cin >> index >> v;
            a[index] = v;
        } else if (strcmp(cmd, "print") == 0) {
            cout << a << "\n\n";
        }
    }
    return 0;
}
