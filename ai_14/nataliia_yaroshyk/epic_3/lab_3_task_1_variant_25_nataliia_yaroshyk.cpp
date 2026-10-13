#include <iostream>
#include <cmath>
using namespace std;

int main(){
    double a = 0.1, b = 1, E = 0.001, SN, SE;
    int k = 10;

    cout << "Обчислення функції\n\n";

    for(double x = 0.1; x < 1; x += (b - a) / k){
        // Обчислення X
        cout << "X = " << x << "    \t";
        
        double d = x;
        SN = d;
        for(int n = 1; n < 20; n++){
            d *= pow(x, 2) / (2 * n * (2 * n + 1));
            SN += d;
        }
        cout << "SN = " << SN << "      \t";

        double c = x;
        int n = 1;
        SE = c;
        while(c > E){
            c *= pow(x, 2) / (2 * n * (2 * n + 1));
            SE += c;
            n++;
        }
        cout << "SE = " << SE << "        \t";
        // Обчислення Y
        double y = (exp(x) - exp(-x)) / 2;
        cout << "Y = " << y << endl;

    }
    return 0;
}