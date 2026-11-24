#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

struct DynamicArray{
    int *data = nullptr;
    size_t capacity = 0;
    size_t size = 0;
    int k = 2;

    int& operator[](size_t index) {
        return data[index];
    }
};

ostream& operator<<(ostream& os, DynamicArray& arr){
    for (size_t i = 0; i<arr.size; i++){
        cout << arr.data[i] << " ";
    }
    cout << "\n";
    return os;
}

void relocateMemory(DynamicArray& arr, size_t newCapacity){
    if (newCapacity<= arr.capacity) return;
    int *temp = arr.data;
    arr.data = new int[newCapacity];
    for (int i = 0; i< arr.size; i++){
        arr.data[i] = temp[i];
    }
    delete temp;
    arr.capacity = newCapacity;
}

void freeArray(DynamicArray& arr){
    if (arr.data == nullptr) return;
    delete arr.data;
    arr.data = nullptr;
    arr.capacity = 0;
    arr.size = 0;
}

void insert(DynamicArray& arr, size_t index, size_t len, int* items){
    size_t newSize = arr.size + len;
    while (newSize >= arr.capacity){
        relocateMemory(arr, arr.capacity*arr.k);
    }
    for (size_t i = arr.size-1+len; i>=index+len; i--){
        arr.data[i]=arr.data[i-len];
    }
    for (size_t i = 0; i<len; i++){
        arr.data[index+i]=items[i];
    }
    arr.size+=len;
}

void erase(DynamicArray& arr, size_t index, size_t len){
    if (index+len>arr.size) return;
    size_t size = arr.size;
    for (size_t i = index; i<size-len; i++){
        arr.data[i] = arr.data[i+len];
    }
    arr.size-=len;
}

void printSize(DynamicArray& arr){
    cout << arr.size << "\n";
}

void printCapacity(DynamicArray& arr){
    cout << arr.capacity << "\n";
}

void get(DynamicArray& arr, size_t index){
    if (index>=arr.size) return;
    cout << arr[index] << "\n";
}

void set(DynamicArray& arr, size_t index, int value){
    if (index>=arr.size) return;
    arr[index] = value;
}

void printData(DynamicArray& arr){
    if (arr.size == 0) return;
    cout << arr;
}

int main(){
    int Q;
    cin >> Q;
    DynamicArray myArr;
    relocateMemory(myArr, 1);
    for (int i = 0; i<Q; i++){
        char action[100];
        cin >> action;

        if (strcmp(action, "size")==0) printSize(myArr);
        if (strcmp(action,"capacity")==0) printCapacity(myArr);
        if (strcmp(action,"insert")==0){
            size_t index, n;
            cin >> index >> n;
            int data[n];
            for (int k = 0; k<n; k++){
                cin >> data[k];
            }
            insert(myArr, index, n, data);
        }
        if (strcmp(action,"erase")==0){
            size_t index, n;
            cin >> index >> n;
            erase(myArr, index, n);
        }
        if (strcmp(action,"get")==0){
            size_t index;
            cin >> index;
            get(myArr, index);
        }
        if (strcmp(action,"set")==0){
            size_t index;
            int value;
            cin >> index >> value;
            set(myArr, index, value);
        }
        if (strcmp(action,"print")==0){
            printData(myArr);
        }
    }
    freeArray(myArr);
    return 0;
}