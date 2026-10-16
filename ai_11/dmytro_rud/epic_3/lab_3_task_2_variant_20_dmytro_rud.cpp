#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

int main() {
    const double eps = 0.0001;
    const int N = 30;
    double a = 0.1, b = 1.0;
    int k = 10;
    double h = (b - a) / k;

    cout << "Обчислення функції" << endl;
    cout << fixed << setprecision(6);

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;
        double t = x / 2;

        // --- SN: рівно N доданків ---
        double c = 1.0;            
        double SN = 1.0;            
        double term = 0.0;
        for (int n = 1; n <= N; n++) {
            c = c * (t / n);        
            term = (pow(n, 2) + 1) * c;   
            SN += term;     
        }

        // --- SE: поки доданок >= eps ---
        c = 1.0;
        double SE = 0.0;
        term = 1.0;
        int n = 0;
        while (term >= eps) {
            SE += term;
            c = c * (t / (n + 1));
            term = (pow(n + 1, 2) + 1) * c;
            n++;
        }

        // --- точне значення ---
        double Y = ((pow(x, 2) / 4) + (x / 2) + 1) * exp(x / 2);

        cout << "X=" << setw(8) << x << 
        "  SN=" << setw(8) << SN << 
        "  SE=" << setw(8) <<SE << 
        "  Y="  << setw(8) << Y << endl;
    }
    return 0;
}