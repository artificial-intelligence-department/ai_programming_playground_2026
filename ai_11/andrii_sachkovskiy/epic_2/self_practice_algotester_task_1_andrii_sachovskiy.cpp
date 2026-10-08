/*
    Задача: self_practice_algotester_task_1 спекотні дні пінгвінів 
    Автор: Сачковський Андрій
    Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    unsigned long long l, w, u, d;
    cin >> l >> w >> u >> d;

    if (l <= w && l <= u + d)//перевірка чи рот пінгвіна робочий
        cout << "Three times Sex on the Beach, please!" << endl;
    else
        cout << "Forget about the cocktails, man!" << endl;

    return 0;
}
