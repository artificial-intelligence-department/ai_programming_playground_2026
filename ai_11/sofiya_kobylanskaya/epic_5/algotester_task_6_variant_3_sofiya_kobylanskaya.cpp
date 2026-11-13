#include <iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;
    if (N < 1 || N > 9)
    {
        return 0;
    }
    int field[9][9];
    char row[10];

    for (int i = 0; i < N; i++)
    {
        cin >> row;

        for (int j = 0; j < N; j++)
        {
            field[i][j] = row[j] - '0';
        }
    }
    int Q;
    cin >> Q;

    if (Q < 1 || Q > 1000)
    {
        return 0;
    }
    int x, y;
    for (int i = 0; i < Q; i++)
    {
        cin >> x >> y;
        if (x < 1 || x > N || y < 1 || y > N)
        {
            return 0;
        }
        if (field[x - 1][y - 1] > 0)
        {
            cout << 1 << endl;
            cout << field[x - 1][y - 1] << endl;
        }
        if (field[x - 1][y - 1] == 0)
        {
            int possible[9];
            int count = 0;

            for (int number = 1; number <= N; number++)
            {
                bool found = false;

                for (int j = 0; j < N; j++)
                {
                    if (field[x - 1][j] == number ||
                        field[j][y - 1] == number)
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    possible[count] = number;
                    count++;
                }
            }

            cout << count << endl;

            for (int j = 0; j < count; j++)
            {
                cout << possible[j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}