/*
Lab_3_task_1
Мельник Олександра ШІ-13 варіант 12*/
#include <iostream>
#include <cmath>  
#include <iomanip> 
/*
функція y=-1/2ln(1-2xcos(pi/3)+x^2)
діапазон зміни аргументу 0.1<=x<=0.8
сума S=(x*cos(pi/3))/1+(x^2*cos(2*pi/3))/2+...+(x^n*cos(n*pi/3))/n*/
using namespace std;

int main() {
    double e = 0.0001;
    int n_max = 35; 
    double step = 0.1;
    double pi = acos(-1.0);

    for (double x = 0.1; x <= 0.81; x += step) 
    {
        //обчислення Y
        double Y = -0.5 * log(1.0 - 2.0 * x * cos(pi / 3.0) + pow(x, 2));
        double SN = 0.0;
        double x_power = x; 
        //обчислення SN
        for (int i = 1; i <= n_max; i++)
        {
            double a = (x_power / i) * cos(i * pi / 3.0);
            SN += a;
            x_power *= x;
        }
        //обчислення SE
        double SE = 0.0;
        int n = 1;
        x_power = x;
        double a = (x_power / n) * cos(n * pi / 3.0);
        
        while (abs(a) >= e) {
            SE += a;
            n++;
            x_power *= x;
            a = (x_power / n) * cos(n * pi / 3.0);
        }

        cout << fixed << setprecision(5);
        cout << "X=" << x;
        cout << "   SN=" << SN;
        cout << "   SE=" << SE;
        cout << "   Y=" << Y << endl; 
    }
    return 0;
}