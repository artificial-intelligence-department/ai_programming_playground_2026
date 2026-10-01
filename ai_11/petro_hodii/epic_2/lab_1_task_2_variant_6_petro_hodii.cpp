 /*
 Лабораторна робота №1, Завдання 2, варіант 6
 Годій Петро
 ШІ-11
 */
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    //Ініціалізую змінні
    int m_0,n_0;
    
    //Отримую значення змінних від користувача
    cout << "Введіть m: ";
    cin >> m_0;

    cout << "Введіть n: ";
    cin >> n_0;

    //Обчслюю перший приклад
    int m = m_0;
    int n = n_0;

    int first = m-++n;

    //Обчислюю другий приклад
    m = m_0;
    n = n_0;

    int second = ++m>--n;

    //Обчислюю третій приклад
    m = m_0;
    n = n_0;

    int third = --n<++m;

    //Виводжу результати
    cout << "Результат для m-++n: " << first << endl;
    cout << "Результат для ++m>--n: " << second << endl;
    cout << "Результат для --n<++m: " << third << endl;

    return 0;
}
