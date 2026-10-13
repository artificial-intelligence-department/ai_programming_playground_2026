/*
Лабораторна робота №2
Варіант 4
Кузовнііков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    int res = 0;
    for (int x = 21; x < 100; x++ ) {
        if (x % 3 == 0){
            res += x;
        }
    }

    cout << "Сума елементів більших за 20, менших за 100 та кратних 3 = " << res << endl;
    
    return 0;
}