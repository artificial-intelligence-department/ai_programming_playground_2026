#include <iostream>
using namespace std;


void printring(int a[], int size, int K) {
    if (size <= 0) {
        cout << "Кільце порожнє." << endl;
        return;
    }
   
    K = K % size;
    if (K < 0) K += size;

    cout << "Виведення, починаючи з елемента з індексом " << K << ": ";
    for (int i = 0; i < size; i++) {
        int currentindex = (K + i) % size;
        cout << a[currentindex] << " ";
    }
    cout << endl;
}

int main() {
    
    const int initialsize = 5;
    int basearr[initialsize] = {17, 12, 88, 13, 53};
    
    
    int ring[100];
    int size = initialsize;
    for (int i = 0; i < size; i++) {
        ring[i] = basearr[i];
    }

    cout << "Пункти 1, 2: Початкове кільце та друк з K-ого елемента" << endl;
    int K;
    cout << "Введіть індекс K (від 0 до " << size - 1 << "): ";
    if (!(cin >> K)) K = 0;
    
    printring(ring, size, K);

    cout << "\nПункт 3: Додати в кільце перший і останній елементи" << endl;
    int firstelem = ring[0];
    int lastelem = ring[size - 1];

    
    for (int i = size; i > 0; i--) {
        ring[i] = ring[i - 1];
    }
    ring[0] = lastelem;
    size++;

    
    ring[size] = firstelem;
    size++;

    cout << "Кільце після додавання першого та останнього елементів:" << endl;
    for (int i = 0; i < size; i++) {
        cout << ring[i] << " ";
    }
    cout << endl;

    cout << "\nПункт 4: Знищити з кільця парні елементи" << endl;
   
    int temp[100];
    int newsize = 0;
    for (int i = 0; i < size; i++) {
        
        if (ring[i] % 2 != 0) {
            temp[newsize++] = ring[i];
        }
    }
    
    for (int i = 0; i < newsize; i++) {
        ring[i] = temp[i];
    }
    size = newsize;

    cout << "Кільце після видалення парних елементів (залишились тільки непарні):" << endl;
    for (int i = 0; i < size; i++) {
        cout << ring[i] << " ";
    }
    cout << endl;

    cout << "\nПункт 5: Роздрукувати отримане кільце, починаючи з К-ого до K-1" << endl;
    if (size > 0) {
        printring(ring, size, K);
    } else {
        cout << "Кільце стало порожнім після видалення всіх елементів." << endl;
    }

    return 0;
}
