/*
    Задача: Алготестер. Лабораторна робота №6. Варіант №3
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int N;
    cin >> N;
    char row[9][10];
    for (int i = 0; i < N; i++)
    {
        cin >> row[i];
    }
    int Q;
    cin >> Q;
    for (int j = 0; j < Q; j++)
    {
        int x,y;
        cin >> x >> y;
        x--;
        y--;
        int result[9];
        int M = 0;
        if (row[x][y] == '0')
        {
            for (int d = 1; d <= N; d++)
            {
                char c = '0' + d;
                bool used = false;
                for (int k = 0; k < N; k++)
                {
                    if (row[x][k] == c || row[k][y] == c)
                    {
                        used = true;
                    }
                }
                if (used == false)
                {
                    result[M] = d;
                    M++;
                }
            }
        }
        else
        {
            result[0] = row[x][y] - '0';
            M = 1;
        }
        cout << M << endl;
        for (int i = 0; i < M; i++)
        {
            if (i > 0)
            {
                cout << " ";
            }
            cout << result[i];
        }
        cout << endl;
        cout << endl;
    }
    return 0;
}