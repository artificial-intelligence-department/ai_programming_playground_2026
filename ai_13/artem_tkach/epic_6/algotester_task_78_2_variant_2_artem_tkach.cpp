// Algotester Lab 78, варіант 2: власна реалізація структури даних «Динамічний масив».
// https://algotester.com/en/ContestProblem/DisplayWithEditor/167981
// Запити: insert, erase, size, capacity, get, set, print.
// Структура написана як шаблон класу (у main параметр - int), без STL-контейнерів (друга частина завдання, 100% балів).
// Початкова ємність 1, фактор росту 2, оператор [] і вивід << перевантажено.

#include <iostream>
#include <string>

template <typename T>
class DynamicArray {
private:
    T *data;
    int count;
    int reserved;   

    void grow(int needed) {
        if (needed < reserved) {
            return;
        }
        int newReserved = reserved;
        while (newReserved <= needed) {
            newReserved = newReserved * 2;
        }

        T *newData = new T[newReserved];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        reserved = newReserved;
    }

public:
    DynamicArray() {
        data = new T[1];
        count = 0;
        reserved = 1;
    }

    ~DynamicArray() {
        delete[] data;
    }

    int getSize() const {
        return count;
    }

    int getCapacity() const {
        return reserved;
    }

    T &operator[](int index) {
        return data[index];
    }

    void insert(int index, const T *values, int amount) {
        grow(count + amount);
        for (int i = count - 1; i >= index; i--) {
            data[i + amount] = data[i];
        }
        for (int i = 0; i < amount; i++) {
            data[index + i] = values[i];
        }
        count = count + amount;
    }

    // Видаляє amount елементів починаючи з позиції index.
    void erase(int index, int amount) {
        if (index + amount > count) {
            amount = count - index;
        }
        for (int i = index; i + amount < count; i++) {
            data[i] = data[i + amount];
        }
        count = count - amount;
    }

    friend std::ostream &operator<<(std::ostream &out, const DynamicArray &array) {
        for (int i = 0; i < array.count; i++) {
            if (i > 0) {
                out << " ";
            }
            out << array.data[i];
        }
        return out;
    }
};

// Запит insert: індекс, кількість, потім самі числа.
void insertQuery(DynamicArray<int> &array) {
    int index, amount;
    std::cin >> index >> amount;
    int *values = new int[amount];
    for (int i = 0; i < amount; i++) {
        std::cin >> values[i];
    }
    array.insert(index, values, amount);
    delete[] values;
}

// Запит erase: індекс і кількість елементів.
void eraseQuery(DynamicArray<int> &array) {
    int index, amount;
    std::cin >> index >> amount;
    array.erase(index, amount);
}

// Запит get: виводить елемент за індексом.
void getQuery(DynamicArray<int> &array) {
    int index;
    std::cin >> index;
    std::cout << array[index] << "\n";
}

// Запит set: змінює елемент за індексом.
void setQuery(DynamicArray<int> &array) {
    int index, value;
    std::cin >> index >> value;
    array[index] = value;
}

// Виконує один запит за його ідентифікатором.
void processQuery(DynamicArray<int> &array, const std::string &command) {
    if (command == "insert") {
        insertQuery(array);
    } else if (command == "erase") {
        eraseQuery(array);
    } else if (command == "size") {
        std::cout << array.getSize() << "\n";
    } else if (command == "capacity") {
        std::cout << array.getCapacity() << "\n";
    } else if (command == "get") {
        getQuery(array);
    } else if (command == "set") {
        setQuery(array);
    } else if (command == "print") {
        std::cout << array << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int queryCount;
    std::cin >> queryCount;

    DynamicArray<int> array;
    for (int q = 0; q < queryCount; q++) {
        std::string command;
        std::cin >> command;
        processQuery(array, command);
    }
    return 0;
}
