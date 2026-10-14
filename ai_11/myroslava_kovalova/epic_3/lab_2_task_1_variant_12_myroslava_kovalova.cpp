/* Лабораторна робота 2, завдання 1, варіант 12
Ковальова Мирослава
ШІ-11
*/
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    
    const double eps = 0.0001;
    double a_n = 2; //значення першого члена
    double sum = a_n;
    double n=1; //першим ми рахуємо другий член послідовності, але беремо n=1, тому що формулу a_(n+1) ми виражали через n

    while(true){
        
        double step1 = n/(n+1);
        double coef = 2*pow(step1,n);
        a_n *=coef;
        if(a_n<eps) break;
        sum +=a_n;
        n++;    
    }
    cout<<"Сума ряду з точністю ε=0.0001: "<<sum<<endl;
    return 0;
}