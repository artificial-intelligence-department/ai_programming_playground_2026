#include <iostream>

using namespace std;

int main() {

    int n = 1;
    double limit_of_precision = 0.0001;
    double a_n = 3.0 * 1 / 6;
    double sum = a_n;

    while(true){
        //за рекурентною формулою
        a_n *= 1.0 / ((3*n + 1) * (3*n + 2));

        if(a_n >= limit_of_precision){
            sum += a_n;
        }
        else{
            break;
        }
        n++;
    }

    cout << "Сума ряду: " << sum << endl;
}