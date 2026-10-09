/*
Назва: Лабораторна робота №1. Варіант 4. Завдання 2.
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream>
using namespace std;
int main(){
    int n, m, res_1;
    cout << "Введіть n: ";
    cin >> n ;
    cout << "Введіть m: ";
    cin >> m;

    int n_s = n; //Присвоєння нових змінних для збереження початкових значень n та m
    int m_s = m;
    res_1 = n_s++*m_s;
    cout << "n: " << n_s << ", m: " << m_s << ", res: " << res_1  << endl << endl;

    n_s = n;
    m_s = m;
    bool res_2 = n_s++ < m_s; //Перевірка у булевому форматі
    cout << "n: " << n_s << ", m: " << m_s << ", res: "<< boolalpha  << res_2 << endl << endl;

    n_s = n;
    m_s = m;
    bool res_3 = m_s-- > m;
    cout << "m--: " << m_s << ", m: " << m << ", res: " << boolalpha  << res_3 << endl;
    


}

