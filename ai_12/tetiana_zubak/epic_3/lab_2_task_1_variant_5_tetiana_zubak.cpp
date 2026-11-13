/*
Лабораторна робота №2, варіант 5
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

const double e = 0.0001;

double a(int n){
    double a0 = pow(-1, n -1)/ pow(n, n);
    return a0;
}

double res(int n){
    double a0 = a(n);
    if(fabs(a0) <= e) return a0;
    return a(n) + res(n+1);
}

int main(){
int n = 1;
string formula = "-n^n / (n+1)^(n+1)";
cout << "Відношення для рекурентної формули a(n+1)/a(n) = " << formula << endl << "Звідси  формула для наступного члена a(n+1) = a(n) * (" << formula << ")" << endl;

double result = res(n);
cout << "Сума ряду з точністю " << e <<": " << result << endl;

return 0;
}