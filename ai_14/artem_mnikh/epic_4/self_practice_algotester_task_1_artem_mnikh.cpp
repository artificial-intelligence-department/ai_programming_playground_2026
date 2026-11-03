#include <cmath>
#include <iostream>

using namespace std;

int n;
int* position;
int counter = 0;

void rec(int currentX)
{
    if (currentX == n)
    {
        ++counter;
        return;
    }
    for (int i = 0; i < n; ++i)
    {
        bool canBePlaced = true;
        for (int j = 0; j < n; ++j)
        {
            if (position[j] == -1)
            {
                continue;
            }
            if (abs(currentX - j) == abs(position[j] - i) || position[j] == i)
            {
                canBePlaced = false;
                break;
            }
        }
        if (canBePlaced)
        {
            position[currentX] = i;
            rec(currentX + 1);
            position[currentX] = -1;
        }
    }
}

int main()
{
    cin >> n;

    position = new int[n];
    for (int i = 0; i < n; ++i)
    {
        position[i] = -1;
    }

    rec(0);
    cout << counter;

    delete[] position;
    return 0;
}