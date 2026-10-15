/*Lab 2 Task 1 Variant 16
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <cmath>
using namespace std;
//Вираз з варіанта 16: a_n  = lg(n!)*e^(-n√n)
int main() {
    const double eps = 0.0001;
    //При a1 значення виразу = 0, тому починаємо з a2
    int n = 2;
    //lg(2!) = lg(2)
    double logFactorial = log10(2.0);
    //перший член ряду a2 = lg(2!)*e^(−2√2)
    double an = logFactorial * exp(-2 * sqrt(2.0));
    double sum = 0;

    while (an >= eps) {
        sum += an;
        /*рекурентна формула
        a_(n+1) = a_n*(lg(n!)+lg(n+1))/lg(n!)*e^(−((n+1)√(n+1) − n√n))*/
        //lg((n+1)!) = lg(n!) + lg(n+1)
        double logNext = logFactorial + log10(n + 1.0);
        //показник експоненти: для a_(n+1)=(n+1)√(n+1), a_n=n√n
        double expNew = (n + 1) * sqrt(n + 1.0);
        double expOld = n * sqrt((double)n);
        //переходимо від a_n до a_(n+1)
        an = an * (logNext / logFactorial) * exp(-(expNew - expOld));
        //logFactorial = lg((n+1)!), а n = n+1
        logFactorial = logNext;
        n++;
    }
    cout << "Сума ряду з точністю eps = " << sum << endl;
    return 0;
}