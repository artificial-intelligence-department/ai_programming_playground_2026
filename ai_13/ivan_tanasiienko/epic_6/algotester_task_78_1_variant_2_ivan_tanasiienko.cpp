/*
    Algotester Lab 78 (1), Variant 2, Танасієнко Іван, ШІ-13
*/
#include <iostream>
#include <cstring>

template<class T>
class DynamicArray
{
    public:
    T* arr = new T[1];
    int size = 0;
    int capacity = 1;

    void Insert()
    {
        int id, elements;
        std::cin >> id >> elements;

        Reserve(size + elements);
        for(int i = size - 1; i >= id; i--) *(arr + i + elements) = *(arr + i);
        for(int j = 0; j < elements; j++) std::cin >> *(arr + id + j);

        size += elements;
    }

    void Erase()
    {
        int id, elements;
        std::cin >> id >> elements;

        for(int i = id; i < size - elements; i++) *(arr + i) = *(arr + i + elements);

        size -= elements;
    }

    void Reserve(int required)
    {
        if(required < capacity) return;

        int newCapacity = capacity;
        while(newCapacity <= required) newCapacity *= 2;

        T* temp = new T[newCapacity];
        for(int i = 0; i < size; i++) *(temp + i) = *(arr + i);

        delete[] arr;
        arr = temp;
        capacity = newCapacity;
    }

    void Size() { std::cout << size << std::endl; }
    void Capacity() { std::cout << capacity << std::endl; }
    T& operator[](int id) { return *(arr + id); }
    ~DynamicArray() { delete[] arr; }
};

template<class T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& obj)
{
    for(int i = 0; i < obj.size; i++)
    {
        if(i > 0) os << ' ';
        os << *(obj.arr + i);
    }
    os << std::endl;
    return os;
}

int main()
{
    int actions, id = 0;
    DynamicArray<int> arr;
    std::cin >> actions;
    char action[32];

    for(int i = 0; i < actions; i++)
    {
        std::cin >> action;
        (strcmp(action, "insert") == 0) ? (arr.Insert(), 0) : (strcmp(action, "erase") == 0) ? (arr.Erase(), 0) : (strcmp(action, "size") == 0) ? (arr.Size(), 0) : (strcmp(action, "capacity") == 0) ? (arr.Capacity(), 0) : (strcmp(action, "set") == 0) ? (std::cin >> id >> arr[id], 0) : (strcmp(action, "get") == 0) ? (std::cin >> id, std::cout << arr[id] << '\n', 0) : (strcmp(action, "print") == 0) ? (std::cout << arr, 0) : 0;
    }

    return 0;
}