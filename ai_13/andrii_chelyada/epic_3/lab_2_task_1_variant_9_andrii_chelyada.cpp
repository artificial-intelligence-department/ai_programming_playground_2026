// lab 2 task 1 variant 9
    // Челяда Андрій, ШІ-13

#include <iostream>
#include <iomanip>

using namespace std;
// Початкова формула a_n = 10^n / n!
// Рекурентна формула a_{n+1} = a_n * 10 / (n + 1), a_1 = 10

int main() {
    const double eps = 0.0001; 
    double a = 10; 
    double sum = 0; 
    int n = 1; 

    while (a >= eps) { 
        sum += a; //
        a = a * 10 / (n + 1);
        n++;
    }
    cout << fixed << setprecision(4) << "Сума ряду: " << sum << endl;

    return 0;
}


