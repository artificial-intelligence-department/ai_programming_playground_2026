/*
Назва задачі: Найбільша пара
Автор: Strazhets Illia
Група: AI-13
*/
#include <iostream>
using namespace std;
int main()
{
    const int MAX = 1000;
    int a_i[MAX];
    int n = 0;

    cin >> n;

    // Перевірка за обмеженнями задачі
    if (n < 2 || n > 1000)
    {
        return 1;
    }
    if (n % 2 != 0)
    {
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> a_i[i];
    }

    // Сортування за зростанням.
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a_i[j] > a_i[j + 1])
            {
                int temp = a_i[j];
                a_i[j] = a_i[j + 1];
                a_i[j + 1] = temp;
            }
        }
    }

    // Перша пара: найменше та найбільше числа.
    int maxSum = a_i[0] + a_i[n - 1];

    // Перевіряємо решту пар.
    for (int i = 1; i < n / 2; i++)
    {
        int sum = a_i[i] + a_i[n - 1 - i];

        if (sum > maxSum)
        {
            maxSum = sum;
        }
    }

    cout << maxSum;
    return 0;
}