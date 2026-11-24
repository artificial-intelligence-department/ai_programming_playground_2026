/*
    Lab 4v14, Момоток Артем, ШІ-13
*/
#include <iostream>
#include <cstdlib>  
#include <ctime>    

using namespace std;

int main()
{
    // 1) Сформувати одновимірний масив цілих чисел, використовуючи генератор випадкових чисел.
    srand(time(nullptr));

    int n;

    do {
        cout << "Введіть довжину масиву (більше 13 елементів): ";
        cin >> n;
    } while (n < 14);

    int* a = new int[n]; 

    for (int* p = a; p < a + n; p++) {
        *p = rand() % 100;
    }

    // 2) Роздрукувати отриманий масив.
    cout << "Початковий масив:" << endl;
    for (int* p = a; p < a + n; p++){
        cout << *p << " ";
    }
    cout << endl;

    // 3) Перевернути масив і, якщо кількість елементів масиву непарна, знищити його середній елемент.
    int* left = a;
    int* right = a + n - 1;
    while (left < right)
    {
        int tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }

    if (n % 2 != 0) {
        for (int* p = a + n / 2; p < a + n - 1; p++){
            *p = *(p + 1);
        }
        n--;
    }

    // 4) Додати на початок масиву 3 елементи зі значенням M[I+10]-2.
    int* b = new int[n + 3];             

    for (int i = 0; i < 3; i++){
        *(b + i) = *(a + i + 10) - 2;
    }

    for (int i = 0; i < n; i++) {
        *(b + i + 3) = *(a + i);    
    }    

    delete[] a;                         
    a = b;                              
    n += 3;

    // 5) Роздрукувати отриманий масив.
    cout << "Отриманий масив:" << endl;
    for (int* p = a; p < a + n; p++){
        cout << *p << " ";
    }

    cout << endl;

    delete[] a;                          
    a = nullptr;

    return 0;
}