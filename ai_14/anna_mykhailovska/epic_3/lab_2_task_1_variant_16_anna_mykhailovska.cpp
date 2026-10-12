/*
    Lab 2
    Михайловська Анна
    ШІ-14
*/

#include <iostream> 
#include <cmath>   
#include <iomanip> 

using namespace std; 

int main() {
    const double eps = 0.0001; // Задана точність e

    int n = 2; 

    double logFact = log10(2.0); // lg(n!)

    // Обчислюємо початковий член: a_n = lg(n!) * e^(-n*sqrt(n)).
    double a = logFact * exp(-n * sqrt(n));

    double sum = 0.0; 
    
    while (a >= eps) {
        sum += a; 

        // lg((n + 1)!) = lg(n!) + lg(n + 1).
        double nextLogFact = logFact + log10(n + 1.0);

        // Обчислюємо наступний член через рекурентну формулу:
        // a_(n+1) = a_n * lg((n+1)!) / lg(n!) * e^(n*sqrt(n) - (n+1)*sqrt(n+1)).
        a *= (nextLogFact / logFact) * exp(n * sqrt(n) - (n + 1.0) * sqrt(n + 1.0));

        logFact = nextLogFact; 
        n++;                 
    }

    cout << "Сума ряду з точністю " << eps << ": " << fixed << setprecision(8) << sum << '\n';

    return 0;
}