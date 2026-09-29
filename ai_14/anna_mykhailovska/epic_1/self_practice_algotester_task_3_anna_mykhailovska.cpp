/*
    Задача: Скільки заплатити?
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
using namespace std;

int main(){
    int a,b;
    cin >> a >> b;

    if (a + 1 < b)
        cout << a + 1;
    else if (b + 1 < a)
        cout << b + 1;
    else
        cout << -1;

    return 0;
}
