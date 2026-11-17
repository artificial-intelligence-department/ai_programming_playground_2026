/*
    Задача: Алготестер. Лабораторна робота №4. Варіант №1_1
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
#include <algorithm>
using namespace std;
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
    sort(N, N+n);
    sort(M, M+m);
    int result[200];
    int size;
    // Різниця N-M
    cout << endl;
    size = set_difference(N, N+n, M, M+m, result)- result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;
    //Різниця M-N
    size = set_difference(M, M+m, N, N+n, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;
    //їх перетин 
    size = set_intersection(N, N+n, M, M+m, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;
    // Їх об`єднання
    size = set_union(N, N+n, M, M+m, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;
    //Їх симетрична різниця
    size = set_symmetric_difference(N, N+n, M, M+m, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;
    return 0;
}