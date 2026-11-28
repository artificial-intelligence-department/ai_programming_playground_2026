#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

template<typename T>
class DynamicArray {
private:
    T* data = nullptr;
    size_t capacity = 0;
    size_t size = 0;
    int k = 2;

    void relocateMemory(size_t newCapacity) {
        if (newCapacity <= capacity) return;
        T* temp = data;
        data = new T[newCapacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = temp[i];
        }
        delete[] temp;
        capacity = newCapacity;
    }

    void freeArray() {
        if (data == nullptr) return;
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }

public:
    DynamicArray() {
        relocateMemory(1);
    }

    ~DynamicArray() {
        freeArray();
    }

    size_t getSize() const{
        return size;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const{
        return data[index];
    }

    void insert(size_t index, size_t len, T* items) {
        size_t newSize = size + len;
        while (newSize >= capacity) {
            relocateMemory(capacity * k);
        }
        for (size_t i = size - 1 + len; i >= index + len; i--) {
            data[i] = data[i - len];
        }
        for (size_t i = 0; i < len; i++) {
            data[index + i] = items[i];
        }
        size += len;
    }

    void erase(size_t index, size_t len) {
        if (index + len > size) return;
        for (size_t i = index; i < size - len; i++) {
            data[i] = data[i + len];
        }
        size -= len;
    }

    void printSize(){
        cout << size << "\n";
    }

    void printCapacity(){
        cout << capacity << "\n";
    }

    void get(size_t index) {
        if (index >= size) return;
        cout << (*this)[index] << "\n";
    }

    void set(size_t index, T value) {
        if (index >= size) return;
        (*this)[index] = value;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const DynamicArray<T>& arr) {
    for (size_t i = 0; i < arr.getSize(); i++) {
        os << arr[i] << " ";
    }
    os << "\n";
    return os;
}

template <typename T>
void printData(const DynamicArray<T>& arr) {
    if (arr.getSize() == 0) return;
    cout << arr;
}

int main() {
    int Q;
    cin >> Q;
    DynamicArray<int> myArr;

    for (int i = 0; i < Q; i++) {
        char action[100];
        cin >> action;

        if (strcmp(action, "size") == 0) myArr.printSize();
        if (strcmp(action, "capacity") == 0) myArr.printCapacity();
        if (strcmp(action, "insert") == 0) {
            size_t index, n;
            cin >> index >> n;
            int data[n];
            for (size_t j = 0; j < n; j++) {
                cin >> data[j];
            }
            myArr.insert(index, n, data);
        }
        if (strcmp(action, "erase") == 0) {
            size_t index, n;
            cin >> index >> n;
            myArr.erase(index, n);
        }
        if (strcmp(action, "get") == 0) {
            size_t index;
            cin >> index;
            myArr.get(index);
        }
        if (strcmp(action, "set") == 0) {
            size_t index;
            int value;
            cin >> index >> value;
            myArr.set(index, value);
        }
        if (strcmp(action, "print") == 0) {
            printData(myArr);
        }
    }

    return 0;
}