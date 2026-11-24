/*  
Задача: Algotester Lab 78(2). Варіант №2.  
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class DynamicArray {
public:
T *data;
int size;
int capacity;

DynamicArray() {
size = 0;
capacity = 1;
data = new T[1];}

~DynamicArray() { delete[] data; }

int size_f() { return size; }
int capacity_f() { return capacity; }

T &operator[](int i) { return data[i]; }

void insert() {
int index, N;
cin >> index >> N;

T *m = new T[N];
for (int i = 0; i < N; i++) cin >> m[i];

if (size + N >= capacity) {
    int updated_capacity = capacity;
        while (size + N >= updated_capacity) updated_capacity *= 2;
            T *updated_data = new T[updated_capacity];
            for (int i = 0; i < size; i++) updated_data[i] = data[i];
            delete[] data;
            data = updated_data;
            capacity = updated_capacity;}

for (int i = size - 1; i >= index; i--) data[i + N] = data[i];
    for (int i = 0; i < N; i++) data[index + i] = m[i];
    size += N;
    delete[] m;}

void erase() {
    int index, n;
    cin >> index >> n;
    for (int i = index + n; i < size; i++) data[i - n] = data[i];
    size -= n;}

void get() {
    int index;
    cin >> index;
    cout << data[index] << '\n';}

void set() {
    int index;
    T new_value;
    cin >> index >> new_value;
    data[index] = new_value;}

};
template <typename T>
ostream &operator<<(ostream &os, const DynamicArray<T> &da) {
    for (int i = 0; i < da.size; i++) {
        if (i > 0) os << " ";
        os << da.data[i];
    }
    return os;
}
int main() {
int Q;
cin >> Q;
DynamicArray<int> da;
char command[16];

for (int i = 0; i < Q; i++) {
    cin >> command;

    if (strcmp(command, "insert") == 0) da.insert();
    else if (strcmp(command, "erase") == 0) da.erase();
    else if (strcmp(command, "size") == 0) cout << da.size_f() << '\n';
    else if (strcmp(command, "capacity") == 0) cout << da.capacity_f() << '\n';
    else if (strcmp(command, "get") == 0) da.get();
    else if (strcmp(command, "set") == 0) da.set();
    else if (strcmp(command, "print") == 0) cout << da << '\n';
    }

    return 0;
}