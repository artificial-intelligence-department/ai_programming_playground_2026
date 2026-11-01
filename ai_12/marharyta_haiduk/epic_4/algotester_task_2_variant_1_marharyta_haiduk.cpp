/*
    Задача: Алготестер. Лабораторна робота №2. Варіант №1
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int N;
    cin >> N;
    int r[100000];
    for (int i = 0; i < N; i++)
    {
        cin >> r[i];
    }
    int min1 = r[0];
    int min2 = r[1];
    int max1 = r[0];
    int max2 = r[1];
    if (min1 > min2)
    {
        int temp = min1;
        min1 = min2;
        min2 = temp;
    }
    if (max1 < max2)
    {
        int temp = max1;
        max1 = max2;
        max2 = temp;
    }
    for (int i = 2; i < N; i++)
    {
        int x = r[i];
        if (x < min1)
        {
            min2 = min1;
            min1 = x;
        }
        else if (x < min2)
        {
            min2 = x;
        }
        if (x > max1)
        {
            max2 = max1;
            max1 = x;
        }
        else if (x > max2)
        {
            max2 = x;
        }
    }
    int v1 = max1 - min2;
    int v2 = max2 - min1;
    int m;
    if (v1 < v2)
    {
        m = v1;
    }
    else 
    {
        m = v2;
    }
    cout << m;
    return 0;
}