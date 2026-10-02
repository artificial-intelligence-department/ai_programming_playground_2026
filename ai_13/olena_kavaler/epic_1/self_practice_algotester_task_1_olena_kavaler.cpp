
/*
Студентка: Олена Кавалер
Група: ШІ-13
Задача: Депутатські гроші
*/

#include <iostream>
using namespace std;

int main() 
{
    long long n;
    cin >> n;

    long long count = 0;

    // Рахуємо купюри від найбільшої (500) до найменшої (1)
    count += n / 500;
    n %= 500;

    count += n / 200;
    n %= 200;

    count += n / 100;
    n %= 100;

    count += n / 50;
    n %= 50;

    count += n / 20;
    n %= 20;

    count += n / 10;
    n %= 10;

    count += n / 5;
    n %= 5;

    count += n / 2;
    n %= 2;

    count += n / 1;
    n %= 1;

    cout << count << "\n";
    return 0;

}