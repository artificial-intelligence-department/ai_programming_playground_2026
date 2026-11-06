#include <iostream>
using namespace std;

int main()
{
    srand(time(NULL));
    int N = 100;
    int arr[N];
    int n;
    cout << "Довжина масиву:";
    cin >> n;
    if (n > 50 || n < 1 || cin.fail()) // Валідація
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка.Довжина повинна бути від 1 до 50.";
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = 1 + rand() % 100;  //Випадкові значення масиву.
    }

    cout << "Початковий масив: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 7 == 0) // видаляємо якщо число кратне 7
        {
            for (int j = i; j < n - 1; j++)
            {
                arr[j] = arr[j + 1]; // зсуваємо вліво при видаленні елемента
            }
            n--;
            i--; // зменшуємо розмір масиву на 1
        }
    }
    for (int i = 0; i < n; i++) // наступне значення від непарного числа  = 0
    {
        if (arr[i] % 2 != 0)
        {
            for (int j = n; j > i + 1; j--) // зсуваємо масив  і вставляємо  нуль.
            {
                arr[j] = arr[j - 1];
            }
            arr[i + 1] = 0;
            n++; // збільшуємо масив на 1
            i++; // пропускаємо наступну ітерацію бо вона 0;
        }
    }
    cout << "Отриманий масив: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}