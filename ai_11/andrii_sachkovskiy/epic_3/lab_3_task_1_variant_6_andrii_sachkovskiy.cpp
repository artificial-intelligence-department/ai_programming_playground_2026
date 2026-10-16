
/*
 * Задача: Lab 3 Task 2 
 * Автор: Сачковський Андрій
 * Група: AI-11
 */
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    const double a = 0.1, b = 1;
    const int k = 10;
    double h = (b - a) / k;  //крок розмір

    double x[k + 1];
    double y[k + 1];
    double sn[k + 1];       
    double se[k + 1];       
    x[0] = a;

    for (int i = 1; i <= k; i++) { //зробив масив і кожен ікс отримав своє значення 
        x[i] = x[i - 1] + h;
    }

    cout << fixed << setprecision(6);

//обчислення y 
    for (int i = 0; i <= k; i++)
    {
        y[i] = exp(x[i] * cos(M_PI / 4)) * cos(x[i] * sin(M_PI / 4));
    }

//сума для n =25;
    const int N = 25;
    const double e = 0.0001;    

    for (int j = 0; j <= k; j++)       
    {
        sn[j] = 1;                      
        double one = 1;                  
        for (int i = 1; i <= N; i++)    
        {
            one = one * i;              
            sn[j] += (cos(i * (M_PI / 4)) * pow(x[j], i)) / one;
        }
    }

//сума для точності e 
    int j = 0;              
    int n = 0;                
    double one = 1;           
    double obrahynok;        
    se[0] = 1;

    while (j <= k)
    {
        n++;
        one = one * n;
        obrahynok = pow(x[j], n) / one;
        se[j] += cos(n * (M_PI / 4)) * obrahynok;

        if (obrahynok < e)    
        {
            j++;              
            if (j <= k)
            {
                se[j] = 1;    
                one = 1;
                n = 0;
            }
        }
    }

    cout << "Обчислення функції" << endl;
    for (int i = 0; i <= k; i++){
        // вихід: X, SN, SE, Y
        cout << "X=" << x[i] << "  SN=" << sn[i]
             << "  SE=" << se[i] << "  Y=" << y[i] << endl;
    }

    return 0;
}