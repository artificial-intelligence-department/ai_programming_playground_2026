/*
    Lab 3 - Task 1-25, Танасієнко Іван, ШІ-13, Варіант 25
*/

#include<iostream>
#include<cmath>
#include<iomanip>

/*
Функція: y = (e^x - e^(-x)) / 2
Сума ряду: S = x + (x^3)/3! + ... + (x^(2n+1))/(2n+1)!
Діапазон: 0.1 <= x <= 1
*/

int main()
{
    const double EPS = 0.0001;
    const double xMIN = 0.1;
    const double xMAX = 1;
    int n = 20;
    int k = 10;
    double x = 0.1;
    double pow, SN, SE, sumF;
    long double a;

    while(x <= 1)
    {
        pow = 0;
        SN = 0;
        a = x;
        //Розрахунок SN
        while(pow <= n)
        {
            //За допомогою рекурентних співвідношень виводимо функцію, яку може порахувати компʼютер
            //an+1 = (an * x^2)/(2n+2)(2n+3)
            SN = SN + a;
            a = (a * std::pow(x, 2)) / ((2 * pow + 2) * (2 * pow + 3));
            pow++;
        }
        //Poзрахунок SE
        pow = 0;
        a = x;
        SE = 0;
        while(a >= EPS)
        {
            SE = SE + a;
            a = (a * std::pow(x, 2)) / ((2 * pow + 2) * (2 * pow + 3));
            pow++;
        }
        //Розрахунок функції
        sumF = (std::exp(x) - std::exp(-x)) / 2;

        std::cout << std::fixed << "X = " << x << " SN = " << SN << 
        " SE = " << SE << " F = " << sumF << std::endl;
        
        x = x + (xMAX - xMIN) / 10;
    }

    return 0;
}