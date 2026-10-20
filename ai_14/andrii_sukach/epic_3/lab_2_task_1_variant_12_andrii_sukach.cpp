/*
Задача: Lab 2 task 1 (variant - 12)
Виконав: Андрій Сукач (ШІ-14)
*/

#include <iostream>
#include <cmath>
using namespace std;
int main(){
    const double e = 0.0001;
    double a = 2;
    double sum = 0.0;
    int n = 1;

    while (a >= e) 
    {
        sum += a;
        a = a * 2* pow((double)n/(n+1),n);
        n++;
    }
cout << "Сума Послідовності: " << sum << " (точність: epsilon = "<< e << ")" << endl;

return 0;
}