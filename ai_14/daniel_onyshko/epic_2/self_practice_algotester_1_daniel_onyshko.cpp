/*
   Задача: Цікава гра (алготестер)
   Онишко Даніель
   Група ШІ-14
 
 */
/*
    Задача: Цікава гра
    Автор: Онишко Даніель
    Група: ШІ-14
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string n_dim, m_dim;
    cin >> n_dim >> m_dim;

    bool is_n_odd = (n_dim.back() - '0') & 1;
    bool is_m_odd = (m_dim.back() - '0') & 1;

    if (is_n_odd && is_m_odd) {
        cout << "Imp";
    } else {
        cout << "Dragon";
    }

    return 0;
}