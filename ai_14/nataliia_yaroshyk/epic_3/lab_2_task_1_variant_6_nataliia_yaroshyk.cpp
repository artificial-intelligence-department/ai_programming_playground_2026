#include <iostream>
#include <cmath>
using namespace std;

int main(){
    double E = 0.0001;
    double sum = 0;
    double a = 5.0/6.0;
    int n = 1;

    while (a > E){
        sum += a;
        a *= (pow(2, n + 1) + pow(3, n + 1)) / (6 * (pow(2, n) + pow(3, n)));
        n++;
    }
    cout << "Сума: " << sum << endl;
    return 0;
}