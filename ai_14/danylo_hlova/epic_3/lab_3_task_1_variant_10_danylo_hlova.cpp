#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
  
    const double A = 0.1;        
    const double B = 1.0;       
    const int K = 10;            
    const int N = 20;            
    const double EPS = 0.0001;   

    double h = (B - A) / K;      // величина кроку

    // таблиця
    cout << fixed << setprecision(6);
    cout << "Обчислення функції y = e^{cos(x)} * cos(sin(x))" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "     X           SN           SE            Y" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // цикл
    for (int i = 0; i <= K; i++)
    {
        double x = A + i * h;  

        double SN = 0.0;
        double fact = 1.0;      // факторіал

        for (int k = 0; k <= N; k++)
        {
            SN = SN + cos(k * x) / fact;  
            fact = fact * (k + 1);         
        }

        double SE = 0.0;
        fact = 1.0;             
        int k = 0;
        double term = 1.0;      

        while (fabs(term) >= EPS)
        {
            SE = SE + term;          
            k = k + 1;
            fact = fact * k;          
            term = cos(k * x) / fact; 
        }

        double Y = exp(cos(x)) * cos(sin(x));

        //  Вивід рядка таблиці 
        cout << setw(10) << x
             << setw(13) << SN
             << setw(13) << SE
             << setw(13) << Y << endl;
    }

    cout << "---------------------------------------------------------------" << endl;

    return 0;
}