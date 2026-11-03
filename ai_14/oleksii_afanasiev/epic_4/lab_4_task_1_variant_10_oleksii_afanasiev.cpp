/*
Задача: Lab 4 Task 1
Виконав: Афанасьєв Олексій (ШІ-14)
*/
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(nullptr));
    int N;
    
    cout << "Введіть кількість елементів масиву: ";
    if(!(cin >> N) || N < 5)
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Помилка: треба ввести ціле число більше за 4" << endl;
            return 1;
    }

    int *arr = new int[N];

    for(int i = 0; i < N; i++)
    {
        arr[i] = rand() % 1000;
    }

    cout << "Масив випадкових чисел:" << endl;
    
    for(int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    int n_to_remove = 5;
    N -= n_to_remove;

    int *arr_new = new int[N];

    for(int i = 0; i < N; i++)
    {
        arr_new[i] = arr[i+n_to_remove];
    }

    delete[] arr;

    arr = arr_new;

    int n_to_add = 3;

    arr_new = new int[N + n_to_add];

    for(int i = 0; i < N; i++)
    {
        arr_new[i] = arr[i];
    }

    for(int i = N; i < N + n_to_add; i++)
    {
        arr_new[i] = rand() % 1000;
    }

    delete[] arr;

    arr = arr_new;

    cout << "Змінений масив після знищення перших 5 елементів та додавання в кінець 3 нових: " << endl;

    for(int i = 0; i < N + n_to_add; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    delete[] arr;
    
    return 0;
}
