/*
    Назва: Депутатські гроші
    Автор: Макух Арсеній
    Група: ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main () {
    int price;
    int bills[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    int count = 0;

    cin >> price;

    if (price < 1 || price > pow(10, 9)) {
        cout << "ERROR" << endl;
        return 0;
    }

    for (int i = 0; i < 9; i++) {
        count += price / bills[i];
        price %= bills[i];
    }
    cout << count << endl;

    return 0;
}