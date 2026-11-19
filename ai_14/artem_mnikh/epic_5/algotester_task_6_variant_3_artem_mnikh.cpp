#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    long long line;
    int field[9][9]{};
    for (int i = 0; i < n; ++i)
    {
        int j = 0;
        cin >> line;
        while (line > 0)
        {
            field[i][n - 1 - j++] = (int)(line % 10);
            line /= 10;
        }
    }
    int Q, y, x, counter;
    int checker[9];
    cin >> Q;
    for (int _ = 0; _ < Q; ++_)
    {
        for (int k = 0; k < n; k++) checker[k] = 1;
        counter = n;
        cin >> y >> x;
        y--;
        x--;
        if (!field[y][x])
        {
            for (int i = 0; i < n; i++)
            {
                if (field[y][i] && checker[field[y][i] - 1] == 1)
                {
                    counter--;
                    checker[field[y][i] - 1] = 0;
                }

                if (field[i][x] && checker[field[i][x] - 1] == 1)
                {
                    counter--;
                    checker[field[i][x] - 1] = 0;
                }
            }
            cout << counter << endl;
            for (int j = 0; j < n; j++)
            {
                if (checker[j]) cout << j + 1 << ' ';
            }
            cout << endl;
        }
        else
            cout << "1\n" << field[y][x] << endl;
    }
}
