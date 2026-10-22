/*
Задача: лабораторна №3 варіант 21
Автор: Хробуст Андрій
Група ШІ-11 
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a = 0.1;
    double b = 1.0;
    int k = 10;
    int n = 40;
    double e = 0.0001;
    double h = (b - a) / k;
    cout << fixed << setprecision(6);
    cout << "X               Sn              Se             y"<<endl;
    for (int j = 0; j <= k; j++) {
        double x = a + j * h;
        //обчислення суми 40 перших членів
        double Sn = 0;
        for (int i = 0; i < n; i++) {
            double element1 = pow(-1.0, i) * pow(x, 2 * i + 1) / (2 * i + 1);
            Sn += element1;
        }
        //обчислення суми до заданої точності е
        double Se = 0;
        double element2 = x;
        int i = 0;
        while (abs(element2) >= e) {
            Se += element2;
            i++;
            element2 = pow(-1.0, i) * pow(x, 2 * i + 1) / (2 * i + 1);
        }
        //вбудована функція арктангенса
        double y = atan(x);
        cout << x << "      " << Sn << "     " << Se << "     " << y << endl;
    }
    return 0;
}
