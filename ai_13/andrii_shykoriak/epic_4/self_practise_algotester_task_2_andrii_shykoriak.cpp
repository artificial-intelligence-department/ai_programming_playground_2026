/*
Умова: Школяре, ти знаєш, що таке матриця? Матриця — це прямокутна таблиця.

Задано матрицю цілих чисел розміру 𝑛 ×𝑚 (з 𝑛 рядків і 𝑚 стовпців). Елемент на перетині 𝑖-ого рядка та 𝑗-ого стовпця матриці позначимо 𝑎𝑖⁢𝑗.

У матриці кожне число зустрічається не більше як двічі.

Твоє завдання — знайти всі числа, що зустрічаються рівно двічі.

Вхідні дані
У першому рядку задано два цілих числа 𝑛 і 𝑚 — розміри матриці.

У наступних 𝑛 рядках записано по 𝑚 цілих чисел 𝑎𝑖⁢𝑗 через пропуск — елементи матриці.

Вихідні дані
У першому рядку виведи ціле число 𝑘 — кількість чисел, що зустрічаються в матриці рівно двічі.

У другому рядку виведи ці числа в будь-якому порядку.
*/

#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    long long n ,m;
    cin >> n >> m;
    long long len = n*m;
    long long matrix[len];
    long long counter = 0;
    long long arr[len] = {0};
    long long index = 0;
    for (long long i = 0; i < len; i++) {
        cin >> matrix[i];
    }
    sort(matrix,matrix + len);
    for (long long i = 0; i < len; i++) {
        if(matrix[i] == matrix[i + 1]){
            arr[index] = matrix[i];
            counter++;
            index++;
        }
    }
    cout << counter << endl;
    for (long long i = 0; i < counter; i++) {
        cout << arr[i] << " ";
    }
    

    return 0;
}