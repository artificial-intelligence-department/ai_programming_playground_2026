/*
Назва задачі: Lab 1v2
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
using namespace std;

int main()
{
    long long h[4];
    long long d[4];

    for (int i = 0; i < 4; i++)
    {
        cin >> h[i];
    }

    for (int i = 0; i < 4; i++)
    {
        cin >> d[i];
    }

    // ERROR має пріоритет: перевіряємо всі відпилювання наперед.
    for (int i = 0; i < 4; i++)
    {
        if (d[i] > h[i])
        {
            cout << "ERROR\n";
            return 0;
        }
    }

    bool overturned = false;

    // Відпилюємо ніжки по черзі.
    for (int i = 0; i < 4; i++)
    {
        h[i] -= d[i];

        long long minHeight = h[0];
        long long maxHeight = h[0];

        for (int j = 1; j < 4; j++)
        {
            if (h[j] < minHeight)
            {
                minHeight = h[j];
            }

            if (h[j] > maxHeight)
            {
                maxHeight = h[j];
            }
        }

        if (maxHeight >= 2 * minHeight)
        {
            overturned = true;
        }
    }

    bool equalHeights = true;

    for (int i = 1; i < 4; i++)
    {
        if (h[i] != h[0])
        {
            equalHeights = false;
        }
    }

    if (!overturned && equalHeights && h[0] > 0)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}
