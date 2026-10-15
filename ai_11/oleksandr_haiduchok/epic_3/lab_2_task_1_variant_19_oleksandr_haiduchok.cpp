#include <iostream>

using namespace std;

int main() {

    double eps = 0.0001;
    double sum = 0;
    double n = 2;
    
    double an = n / ((n - 1) * (n - 1));

    while (an >= eps) {
        sum += an;
        n++;
        an = an * (n * (n - 2) * (n - 2)) / ((n - 1) * (n - 1) * (n - 1));
    }
    cout << "Сума ряду: " << sum << endl;

    return 0;
}