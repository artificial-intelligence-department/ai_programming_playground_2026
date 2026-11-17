/*
    Задача: Алготестер. Лабораторна робота №4. Варіант №1_2
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
void printSet(int size, int result[])
{
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
}
void sortArray(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main() {
    int n;
    cin >> n;
    int N[100];
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
    }
    int m;
    cin >> m;
    int M[100];
    for (int i = 0; i < m; i++)
    {
        cin >>  M[i];
    }
    int result[200];
    bool usedN[100], usedM[100];
    sortArray(N, n);
    sortArray(M, m);
    // Різниця N-M
    int size = 0;
    for (int j = 0; j <m; j++)
    {
        usedM[j] = false;
    }
    for (int i = 0; i < n; i++)
    {
        bool found = false;
        for (int j = 0; j < m; j++)
        {
            if (!usedM[j] && N[i] == M[j])
            {
                usedM[j] = true;
                found = true;
                break;
            }
        }
        if (found == false)
        {
            result[size] = N[i];
            size++;
        }
    }
    printSet(size, result);
    cout << endl;
    //Різниця M-N
    size = 0;
    for (int j = 0; j <n; j++)
    {
        usedN[j] = false;
    }
    for (int i = 0; i < m; i++)
    {
        bool found = false;
        for (int j = 0; j < n; j++)
        {
            if (!usedN[j] && M[i] == N[j])
            {
                usedN[j] = true;
                found = true;
                break;
            }
        }
        if (found == false)
        {
            result[size] = M[i];
            size++;
        }
    }
    printSet(size, result);
    cout << endl;
    //їх перетин
    size = 0;
    for (int j = 0; j <m; j++)
    {
        usedM[j] = false;
    }
    for (int i = 0; i < n; i++)
    {
        bool found = false;
        for (int j = 0; j < m; j++)
        {
            if (!usedM[j] && N[i] == M[j])
            {
                usedM[j] = true;
                found = true;
                break;
            }
        }
        if (found == true)
        {
            result[size] = N[i];
            size++;
        }
    }
    printSet(size, result);
    cout << endl;
    // Їх об`єднання
    size = 0;
    for (int i = 0; i < n; i++)
    {
        result[size] = N[i];
        size++;
    }
    for (int j = 0; j < n; j++)
    {
        usedN[j] = false;
    }
    for (int i = 0; i < m; i++)
    {
        bool found = false;
        for (int j = 0 ; j < n; j++)
        {
            if (!usedN[j] && M[i] == N[j])
            {
                usedN[j] = true;
                found = true;
                break;
            }
        }
        if (found == false)
        {
            result[size] = M[i];
            size++;
        }
    }
    sortArray(result, size);
    printSet(size, result);
    cout << endl;
    //Їх симетрична різниця
    size = 0;
    for (int j = 0; j <m; j++)
    {
        usedM[j] = false;
    }
    for (int i = 0; i < n; i++)
    {
        bool found = false;
        for (int j = 0; j < m; j++)
        {
            if (!usedM[j] && N[i] == M[j])
            {
                usedM[j] = true;
                found = true;
                break;
            }
        }
        if (found == false)
        {
            result[size] = N[i];
            size++;
        }
    }
    for (int j = 0; j < m; j++)
    {
        if (usedM[j] == false)
        {
            result[size] = M[j];
            size++;
        }
    }
    sortArray(result, size);
    printSet(size, result);
    return 0;
}