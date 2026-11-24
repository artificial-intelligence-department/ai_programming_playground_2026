/*  
Задача: Algotester Lab 78(1). Варіант №2.  
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
#include <cstring>
using namespace std;

struct DynamicArray {int *data; int size; int capacity;
int &operator[](int i) {return data[i];}
};

ostream &operator<<(ostream &os, const DynamicArray &da) {
    for(int i = 0; i < da.size; i++) {
        if(i > 0) os << " ";
        os << da.data[i];
    }
    return os;
}

void insert(DynamicArray &da) {
int index, N;
cin >> index >> N;

int *m = new int[N];
    for (int i = 0; i < N; i++) cin >> m[i];

if(da.size + N >= da.capacity) {
    int updated_capacity = da.capacity;
    while (da.size + N >= updated_capacity) updated_capacity *= 2;
        int *updated_data = new int[updated_capacity];
        for (int i = 0; i < da.size; i++) updated_data[i] = da.data[i];
        delete[] da.data;
        da.data = updated_data;
        da.capacity = updated_capacity;}

for (int i = da.size - 1; i >= index; i--) da.data[i + N] = da.data[i];
for (int i = 0; i < N; i++) da.data[index + i] = m[i];
    da.size += N;
    delete[] m;
}
    
void erase(DynamicArray &da) {
    int index, n;
    cin >> index >> n;
    for (int i = index + n; i < da.size; i++) da.data[i - n] = da.data[i];
    da.size -= n;
}

void get(DynamicArray &da) {
    int index;
    cin >> index;
    cout << da[index] << '\n';
}

void set(DynamicArray &da) {
    int index, new_value;
    cin >> index >> new_value;
    da[index] = new_value;
}


int main() {
int Q;
cin >> Q;
DynamicArray da;
da.size = 0;
da.capacity = 1;
da.data = new int[1];
char command[16];
for (int i = 0; i < Q; i++) {
        cin >> command;

        if (strcmp(command, "insert") == 0) {
            insert(da);
        } else if (strcmp(command, "erase") == 0) {
            erase(da);
        } else if (strcmp(command, "size") == 0) {
            cout << da.size << '\n';
        } else if (strcmp(command, "capacity") == 0) {
            cout << da.capacity << '\n';
        } else if (strcmp(command, "get") == 0) {
            get(da);
        } else if (strcmp(command, "set") == 0) {
            set(da);
        } else if (strcmp(command, "print") == 0) {
            cout << da << '\n';
        }
    }

    delete[] da.data;

    return 0;
}