#include <iostream>
#include <cmath>
using namespace std;

int main(){
    long double sum = 0;
    for (int i = 1; i <= 7; i++){
        double res = (i*i) * exp(-sqrt(i));
        sum += res;
    }
    cout << sum << endl;
    return 0;
}