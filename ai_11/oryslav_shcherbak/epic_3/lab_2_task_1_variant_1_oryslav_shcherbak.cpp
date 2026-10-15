#include <iostream>
using namespace std;

/* Задача: Лабораторна робота 2, завдання 1 (варіант 1)
* Щербак Орислав
* Група ШІ - 11
*/

int main(){
    int sum = 0;
    for (int i = 0; i < 200; i +=3){
        sum += i;
    }
    cout << sum << endl;
    return 0;
}