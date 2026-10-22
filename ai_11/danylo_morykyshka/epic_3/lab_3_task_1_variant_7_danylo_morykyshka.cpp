#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a = 0.1;
    double b = 1;
    int k = 10;
    double x;
    double step = (b -a)/k;
    double epsilon = 0.0001;
    double result = 0;
    double sum = 0;

    for(int i = 0;i <= k;i ++){

        double x = a + i * step;

        double result = 1.0;
        double SN = 1.0;

        for (int n = 1; n <= 10; n++)
        {
            result = -result * x * x / ((2 * n - 1) * (2 * n));
            SN += result;
        }

        result = 1.0;
        double SE = 0.0;
        int n = 0;

        while(abs(result) >= epsilon){
        SE += result;
        n++;
        result = -result * x * x / ((2 * n - 1) * (2 * n));
        }
        double Y = cos(x);
        cout << "X=" << x << "  SN=" << SN << "  SE=" << SE << "  Y=" << Y << '\n';
    
    }

   
}