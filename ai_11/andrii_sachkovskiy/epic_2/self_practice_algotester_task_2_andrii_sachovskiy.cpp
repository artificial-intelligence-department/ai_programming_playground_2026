/*
    Задача: self_practice_algotester_task_2  хелловін 
    Автор: Сачковський Андрій
    Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main() {
    int n, m, x;
    cin >> n >> m;

    int min_a = 1001;   // більше за будь-яку можливу ціну 
    int i = 0;
    while (i <n ) {//пошук мінімума
        cin >> x;
        if (x < min_a) min_a = x;
        i++;
    }

    int min_b = 1001;
    int j = 0;
    while (j < m) {
        cin >> x;
        if (x < min_b) min_b = x;
        j++;
    }

    cout << min_a + min_b << endl;
    return 0;
}