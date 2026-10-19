#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main (){

    double a = 0.1; //початок діапазону
    double b = 1.0; //кінець діапазону
    int n = 20; //к-сть доданків
    int k = 10; //к-сть кроків
    double eps = 0.0001; //точність
    double h;

    h = (b - a) / k;

    cout << "h = " << h << endl;

    cout<<"Обчислення функції" <<endl;

    cout << fixed << setprecision(6) << left;

    for(int i = 0;i <= k; i++){
        double x = a + i * h;
        
        double SN = 1.0;
        double factorial = 1.0;
        
        for(int j = 1; j <= n;j++){
            factorial *= j;
            double term = (cos(j * x)/factorial);
            SN += term;
        }

        double SE = 1.0;
        double factorialE = 1.0;
        int j = 1;
        double termE = 1.0;

        while(fabs(termE) >= eps){
            factorialE *= j;
            termE = cos(j * x)/factorialE;
            SE += termE;
            j++;
        }

        double Y;
        Y= exp(cos(x))*cos(sin (x));

        cout<<"X= "<<setw(8)<< x <<" SN= "<<setw(9) << SN <<" SE= "<< setw(9) << SE <<" Y= "<< setw(9) << Y << endl;

    }


    return 0;
}