/*
* Задача: Лабораторна робота 2, варіант 5
* Поліщук Вероніка
* Група 14
*/

#include <iostream> 
#include <cmath>

using namespace std;


int main(){
    double eps=0.0001;
    double sum = 0, a=1;
    int n=1;
    while (fabs(a) >= eps ){
        sum += a;
        a = a * (- pow(n,n) / pow(n+1, n+1));
        n++;
    }
    cout << "Сума ряду = " << sum << endl;
    return 0;
}