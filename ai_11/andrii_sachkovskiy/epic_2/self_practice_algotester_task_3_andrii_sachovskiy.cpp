/*
    Задача: self_practice_algotester_task_3 цікава гра 
    Автор: Сачковський Андрій
    Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if ((n * m) % 2 == 1)
        cout << "Imp" << endl;
    else
        cout << "Dragon" << endl;
    return 0;
}