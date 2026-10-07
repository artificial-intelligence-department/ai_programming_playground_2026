/*
   Задача: Цікава гра (алготестер)
   Онишко Даніель
   Група ШІ-14
 
 */
#include <iostream>
#include <string>
using namespace std;


int main() {
    string n, m;
    cin >> n >> m;


    bool nOdd = (n.back() - '0') % 2 == 1;
    bool mOdd = (m.back() - '0') % 2 == 1;


    if (nOdd && mOdd)
        cout << "Imp";
    else
        cout << "Dragon";


    return 0;
}
