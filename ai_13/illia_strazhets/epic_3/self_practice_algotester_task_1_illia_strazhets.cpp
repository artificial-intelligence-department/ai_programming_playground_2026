/*
Назва задачі: Перехід дороги
Автор: Strazhets Illia
Група: AI-13
*/
#include <iostream>
using namespace std;

const int MAX = 1000000; // Має відповідати обмеженню задачі.
int a_i[MAX];

int main()
{
    int n = 0;
    cin >> n;

    if (n < 1 || n > MAX)
        return 1;

    for (int i = 0; i < n; i++)
    {
        cin >> a_i[i];
    }

    int count = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if ((a_i[i] % 2 == 0) != (a_i[i + 1] % 2 == 0)) // Перевірка якщо перше число парне, а друге - ні, і навпаки - +1 перехід дороги
        {
            count++;
        }
    }

    cout << count;
    return 0;
}