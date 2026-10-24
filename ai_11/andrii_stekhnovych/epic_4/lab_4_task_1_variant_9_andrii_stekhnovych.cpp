// Лабораторна робота 4 варіант 9 
// Стехнович Андрій ШІ-11
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main(){
    srand(time(0));
    cout << "Суть завдання:\nЗгенерувати масив випадкових чисел, вивести його, знищити перший елемент, зсунути циклічно на К елементів вправо, роздрукувати." << endl;
    int n;
    n:
    cout << "Введіть розмір масиву(0-100): ";
    cin >> n;
    if (cin.fail() or n<=0 or n>100) {
        cout << "======================\nВведіть коректне значення N!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto n;
        
    }
    int array[100];
    cout << "======================\nПочатковий масив: " << endl;
    for (int i = 0; i<n; i++) {
        array[i]= rand() % 100;
        cout << array[i] << " ";
    }
    cout << endl;
    int d;
    d:
    cout << "Введіть, який елемент потрібно видалити: ";
    cin >> d;
    if (cin.fail()) {
        cout << "======================\nВведіть коректне значення d!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto d;
        
    }
    int element_index = -1;
    for (int i = 0; i<n; i++) {
        if (array[i]==d) {
            element_index = i;
            break;
        }
    }
    if (element_index!=-1) {
        for (int i = element_index; i<n-1; i++) {
            array[i]=array[i+1];

        }
        n-=1;
    } else {
        cout << "Такого елемента немає в масиві."<<endl;
    }
    cout << "======================\nМасив після видалення: " << endl;
    for (int i = 0; i<n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
   
    int k;
    k:
    cout << "============================\nВведіть параметр зсуву: "<< endl;
    cin >> k;
    if (cin.fail() or k<0) {
        cout << "======================\nВведіть коректне значення k!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto k;
    }
    if (n > 0) {
    k %= n;
    int copyarray[100] = {0};
    for (int i = 0; i < n - k; i++) {
        copyarray[i + k] = array[i];
    }
    for (int i = 0; i < k; i++) {
        copyarray[i] = array[n - k + i];
    }
    cout << "============================\nЗсунутий масив: " << endl;
    for (int i = 0; i < n; i++) {
        cout << copyarray[i] << " ";
    }
    cout << endl;
    } else {
        cout << "============================\nМасив порожній, зсув неможливий." << endl;
    }


}