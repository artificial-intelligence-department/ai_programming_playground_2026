/*
    Задача: Алготестер. Лабораторна №4. Рішення з STL
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    int N[100];
    for (int i = 0; i < n; i++) {
        cin >> N[i];
    }
    int m;
    cin >> m;
    int M[100];
    for (int i = 0; i < m; i++) {
        cin >> M[i];
    }

    // set_* працюють лише з відсортованими масивами, тому сортуємо
    sort(N, N + n);
    sort(M, M + m);

    int result[200];
    int size;

    // Різниця N-M
    // set_difference повертає вказівник на кінець записаного, а "- result" перетворює його на кількість.
    size = set_difference(N, N + n, M, M + m, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Різниця M-N
    // Те саме, але масиви поміняні місцями
    size = set_difference(M, M + m, N, N + n, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Їх перетин
    size = set_intersection(N, N + n, M, M + m, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Їх об'єднання
    size = set_union(N, N + n, M, M + m, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Їх симетрична різниця
    size = set_symmetric_difference(N, N + n, M, M + m, result) - result;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    return 0;
}