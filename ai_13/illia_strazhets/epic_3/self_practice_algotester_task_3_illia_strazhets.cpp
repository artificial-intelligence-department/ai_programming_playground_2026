/*
Назва задачі: Нечесний розподіл
Автор: Strazhets Illia
Група: AI-13
*/
#include <iostream>
using namespace std;
int main()
{
    const int MAX = 4;
    int a = 0, b = 0, c = 0, d = 0;
    cin >> a >> b >> c >> d;
    if ((a < 0 || b < 0 || c < 0 || d < 0) || (a > 100 || b > 100 || c > 100 || d > 100)) // Обмеження умовою задачі
    {
        return 1;
    }
    int arr[MAX];
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    for (int j = 0; j < MAX - 1; j++) // Сортування бульбашкою для того щоб зручно взяти найменше та найбільше значення
    {
        for (int i = 0; i < MAX - j - 1; i++)
        {
            int temp = 0;
            if (arr[i] < arr[i + 1])
            {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }

    int marichkaValue = arr[0] + arr[3]; // Обчислення найбільше значення + найменше значення
    int zenykValue = arr[1] + arr[2];    // Обчислення залишкових значень

    if (marichkaValue > zenykValue)
    {
        cout << "Marichka";
    }

    else if (zenykValue > marichkaValue)
    {
        cout << "Zenyk";
    }

    else
    {
        cout << "Love always wins";
    }
    return 0;
}
