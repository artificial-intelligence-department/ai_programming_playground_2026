/*
Лабораторна робота №2, Завдання №1, Варіант №3.
Цебуля Вадим
ШІ-12
*/
#include <iostream>
using namespace std;

int main(){
        int sum = 0;
        for (int i = 0; i < 200; i++){
                if (i % 2 != 0 && i > 0)
                sum += i;
        }
        cout << "Сума цілих додатніх непарних чисел, менших 200: " << sum << endl;
        return 0;
}