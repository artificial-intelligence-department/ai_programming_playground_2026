/* Лабораторна 1 завдання 2
   Варіант 19
   Ярошик Наталія
   ШІ-14
*/
#include <iostream>
using namespace std;

int main(){
    double n, m;
    cin >> n;
    cin >> m;

    double step1 = --m-++n;
    cout << "Результат 1: " << step1 << endl;

    double step2 = (m * n) < n;
    n++;
    cout << "Результат 2: " << step2 << endl;

    double step3 = n > m;
    n--;
    m++;
    cout << "Результат 3: " << step3 << endl;

    return 0;
}