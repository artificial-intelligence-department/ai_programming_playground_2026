#include <iostream>
#include <cstdlib> // Для rand()
#include <ctime>   // Для time()
using namespace std;

// Функція для виводу масиву на екран
void print(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(NULL)); // Ініціалізуємо генератор випадкових чисел поточним часом

    const int N = 100; // Виділяємо масив з запасом
    int M[N];

    int n;
    cin >> n;

    // залишиться < 4 елементів. Тоді формула M[i+1]+2 не буде виконуватись повністю
    if (n < 9) { 
        cout << "Для виконання всіх пунктів програми n має бути >= 9" << endl;
        return 0; 
    }
    
    // Формування масиву випадкових чисел від 0 до 19
    for (int i = 0; i < n; i++) {
        M[i] = rand() % 20;
    }

    // Вивід початкового масиву
    print(M, n);

    int M_1[N];

    // Видалення останніх 5 елементів
    for (int i = 0; i < n - 5; i++) {
        M_1[i] = M[i];
    }

    print(M_1, n - 5);

    int M_2[N];

    // Додавання в початок масиву 3 елементи зі значенням M[I+1]+2
    for (int i = 0; i < 3; i++) {
        M_2[i] = M_1[i + 1] + 2;       
    }


    // Зсув старих даних
    for (int i = 3; i < n - 2; i++) {
        M_2[i] = M_1[i - 3];     
    }

    print (M_2, n - 2);
    
    return 0;
}