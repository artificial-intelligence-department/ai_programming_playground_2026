/*
Епік 2. self practice: Algotester, задача "Депутатські гроші"
Автор: Кобилянська Софія
Група: ші-11
*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int result = 0;

    result += n / 500;
    n %= 500;
    result += n / 200;
    n %= 200;
    result += n / 100;
    n %= 100;
    result += n / 50;
    n %= 50;
    result += n / 20;
    n %= 20;
    result += n / 10;
    n %= 10;
    result += n / 5;
    n %= 5;
    result += n / 2;
    n %= 2;
    result += n / 1;
    n %= 1;

    cout << result << endl;

    return 0;
}