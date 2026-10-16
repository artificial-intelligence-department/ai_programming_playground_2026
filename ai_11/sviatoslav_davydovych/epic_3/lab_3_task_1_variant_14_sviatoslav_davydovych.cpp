/* Лабораторна робота N.3
Варіант: 14
Автор: Давидович Святослав
Група: ШІ-11 */

#include <iostream>
#include <cmath> // функція cos()

using namespace std;

// не використовуємо рекурентні співвідношення через простоту прямої формули
double sequence(int n, double x){
    int sign = (n%2==0) ? 1 : -1;

    return sign*cos(x*n)/(n*n);
}

int main() {
    constexpr double E = 0.0001; // точність
    constexpr int N = 20; // кількість ітерацій
    const double pi = 2 * asin(1.0); // використовуємо арксинус для визначення числа пі
    const double MIN_X = pi/5;
    const double MAX_X = pi;
    const double step = (MAX_X-MIN_X)/10;

    printf("              Обчислення функції\n");
    for (double x = MIN_X; x<=MAX_X; x+=step){
        double SN = 0;
        double SE = 0;
        double Y = (x*x-pi*pi/3)/4;
        
        // рахує суму для кількості ітерацій N
        for (int i = 1; i<=N; i++){
            SN+=sequence(i,x);
        }

        // рахує суму для заданої точності
        double current;
        int current_n = 1;
        do{
            current=sequence(current_n, x);
            SE+=current;
            current_n++;
        } while (abs(current)>E);
        
        /*вивід у форматі: X=...... SN=...... SE=..... Y=......  */
        printf("X=%+.4f | SN=%+.4f | SE=%+.4f | Y=%+.4f\n",x,SN,SE,Y);
    }
    printf("\n\n");
    return 0;
}