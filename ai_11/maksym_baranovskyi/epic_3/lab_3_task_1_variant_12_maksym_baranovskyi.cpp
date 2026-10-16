#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    const double PI = std::acos(-1.0);
    double epsilon;

    cout << "Введіть значення epsilon: " << endl;
    cin >> epsilon;

    double a = 0.1;
    double b = 0.8;
    int k = 10;
    double step = (b-a)/k;
    int n = 35;
    
 
    double eTerm = 0;

    for(double x = a; x <= b + step / 2; x += step){

        double y = -0.5 * log(1.0 - 2.0 * x * cos(PI / 3.0) + x * x);

        double SN = 0;

        for(int i = 1; i <= n; i++){ 
            double nTerm = (pow(x, i) * cos(i * PI / 3))/i;
            SN += nTerm;

        }

        double SE = 0.0;   
        int i = 1; 
        double eTerm = (pow(x, i) * cos(i * PI / 3.0)) / i;

        while(fabs(eTerm) > epsilon){
            SE += eTerm;
            i++;
            eTerm = (pow(x, i) * cos(i * PI / 3.0)) / i;
            
        }  

        cout << fixed << setprecision(2) << setw(8) << "X = " << x 
             << setprecision(6) << setw(16) << "SN = " << SN
             << setw(16) << "SE = " << SE
             << setw(16) << "Y = " << y << endl;

    }

    return 0;
}