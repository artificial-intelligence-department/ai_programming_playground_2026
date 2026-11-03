/*
    Задача: Алготестер. Лабораторна робота №3. Варіант №3
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
int main() {
    string S;
    cin >> S;
    int count = 1;
    for (int i = 0; i < S.length(); i++)
    {
        if (S[i] == S[i+1])
        {
            count++;
        }
        else
        {
            cout << S[i];
            if (count > 1)
            {
                cout << count;
            }
            count = 1;
        }
    }
    return 0;
}