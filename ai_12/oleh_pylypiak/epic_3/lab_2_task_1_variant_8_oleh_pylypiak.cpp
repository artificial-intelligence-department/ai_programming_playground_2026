/*  Lab 2 Task 1 Variant 8
    Автор:Пилип'як Олег Васильович
    Група: ШІ-12, 3-тя група */
#include <iostream>
using namespace std;

int main () {
    const double E=0.0001;
    int n=0;
    double a=0.5; //перший член(n=1), а=(2*1-1)/2^1=0.5
    double S=0.0;
    while (a>=E){
        n++;
        S+=a;
        a=a*(2.0*n + 1.0)/(2*(2.0*n - 1.0));
    }
    cout << n <<endl;
    cout << "Сума ряду членів S=" << S << endl;
    return 0;
}