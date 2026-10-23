// Задача Алготестер "Коля, Вася і Теніс"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    string s;
    cin >> n >> s;

    int a = 0, b = 0;       // очки Колі та Васі в поточній партії
    int wa = 0, wb = 0;     // виграні партії Колі та Васі

    for (int i = 0; i < n; i++) 
    {
        if (s[i] == 'K') a++;
        else b++;

        // партія закінчена: хтось >= 11 і перевага >= 2
        if (max(a, b) >= 11 && abs(a - b) >= 2)
        {
            if (a > b) wa++;
            else wb++;
            a = 0;
            b = 0;
        }
    }
    cout << wa << ":" << wb << endl;
    if (a != 0 || b != 0)         // остання партія не дограна
        cout << a << ":" << b << endl;

    return 0;
}