/*
Задача: Депутатські гроші (алготестер)
Карпінський Віталій
СШІ-14
*/
#include <iostream>

using namespace std;

int main() {
    long long n; // Вводимо суму грошей
    cin >> n;

    long long count = 0; // Сюди будемо додавати кількість купюр

    count += n / 500;
    n = n % 500;

    count += n / 200;
    n = n % 200;

    count += n / 100;
    n = n % 100;

    count += n / 50;
    n = n % 50;

    count += n / 20;
    n = n % 20;

    count += n / 10;
    n = n % 10;

    count += n / 5;
    n = n % 5;

    count += n / 2;
    n = n % 2;

    count += n / 1;
    cout << count << endl;

    return 0;
}