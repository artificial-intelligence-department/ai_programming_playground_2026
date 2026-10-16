/* Лабораторна робота 3, завдання 1, варіант 23
Ковальова Мирослава
ШІ-11
*/

#include <iostream>
#include <cmath>
using namespace std;
int main(){

    const float a = 0.1;
    const float b = 1;
    const int k = 10;
    double n_max = 15;
    float step = (b-a)/k;
    float x=a;
    double eps = 0.0001;

    for (;x<=b;x+=step){
        double y=2*(cos(x)*cos(x)-1);
        double y_n=-2*(x*x);   //порахували перший елемент
        
        //оголуємо суми кожен раз з новим х, щоб не використовувати результати минулих ітерацій
        double sum_n =y_n;
        double sum_e =y_n;
        
        //формулу для а_(n+1) виведена через a_n, відповідно починаємо з n=1, для пошуку у_2
        for(double n = 1;n<n_max;n++){
            y_n *=-(pow((2*x),2))/((2*n+1)*(2*n+2));
            sum_n +=y_n;
        }
        double n = 1;
        y_n=-2*(x*x);
        while(true){
            y_n *=-(pow((2*x),2))/((2*n+1)*(2*n+2));
            if(abs(y_n)<eps) break;
            sum_e +=y_n;
            n++;    
    }

    cout<<"X = "<<x<< "  SN = "<<sum_n<<"  SE = "<<sum_e<<"  Y = "<<y<<endl;
    }
    return 0;
}