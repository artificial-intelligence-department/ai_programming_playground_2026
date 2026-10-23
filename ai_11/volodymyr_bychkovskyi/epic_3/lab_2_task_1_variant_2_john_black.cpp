/*
Назва: лабораторна робота 2 Варіант 2
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
using namespace std;

int sumPlus2(int i) {
    if (i >= 100) {
        return 0;
    }
    return i + sumPlus2(i + 2);
}

int main() {
    int sum = sumPlus2(0);
    cout << sum << endl;

    return 0;
}