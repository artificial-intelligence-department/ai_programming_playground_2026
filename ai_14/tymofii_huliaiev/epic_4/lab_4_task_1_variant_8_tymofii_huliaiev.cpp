#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));

    int n;
    cout << "Введіть початковий розмір масиву: ";
    if (!(cin >> n) || n <= 0) return 0;

    int* arr = new int[n];
    for(int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 20 + 1;
    }

    cout << "Початковий масив: \n";
    for(int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    int target;
    cout << "Введіть значення яке потрібно видалити: ";
    cin >> target;

    int new_n = 0;
    for(int i = 0; i < n; ++i)
    {
        if(arr[i] != target)
        {
            new_n++;
        }
    }

    int* temp_arr = new int[new_n];
    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        if(arr[i] != target)
        {
            temp_arr[index] = arr[i];
            index++;
        }
    }
    delete[] arr;
    arr = temp_arr;
    n = new_n;

    cout << "Масив після видалення елементів зі значенням " << target << ":\n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";

    cout << "\n";

    int even_count = 0;
    for(int i = 0; i < n; ++i)
    {
        if(arr[i] % 2 == 0)
        {
            even_count++;
        }
    }

    int final_n = n + even_count;
    int* final_arr = new int[final_n];

    index = 0;
    for(int i = 0; i < n; ++i)
    {
        if(arr[i] % 2 == 0)
        {
            final_arr[index] = 0;
            index++;
        }
        final_arr[index] = arr[i];
        index++;
    }
    delete[] arr;
    arr = final_arr;
    n = final_n;

    cout << "Фінальний масив: \n";
    for(int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
    delete[] arr;
}