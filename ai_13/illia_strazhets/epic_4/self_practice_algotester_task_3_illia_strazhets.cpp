/*
Algotester self practice 3
Задача: Повторювані числа в матриці
Автор: Illia Strazhets
Група: AI-13
*/
#include <iostream>
#include <algorithm> // для sort
using namespace std;

// Головна функція: пошук чисел матриці, що зустрічаються рівно двічі
int main()
{
    int rows, cols;
    cin >> rows >> cols;

    // 1. Виділяємо динамічну 2D-матрицю і зчитуємо її
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            cin >> matrix[i][j];
        }
    }

    // 2. Переписуємо всі елементи в один 1D-масив
    int total = rows * cols;
    int *arr = new int[total];
    int idx = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[idx++] = matrix[i][j];
        }
    }

    // 3. Швидке сортування всіх чисел
    sort(arr, arr + total);

    // 4. Знаходимо числа, які повторюються двічі (стоять поруч після сортування)
    int *ans = new int[total / 2 + 1];
    int k = 0;
    for (int i = 0; i < total - 1; i++)
    {
        if (arr[i] == arr[i + 1])
        {
            ans[k++] = arr[i];
            i++; // Перестрибуємо другий елемент пари
        }
    }

    // 5. Виводимо кількість і самі числа
    cout << k << "\n";
    for (int i = 0; i < k; i++)
    {
        cout << ans[i] << " ";
    }

    // 6. Звільняємо всю динамічну пам'ять
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] arr;
    delete[] ans;

    return 0;
}