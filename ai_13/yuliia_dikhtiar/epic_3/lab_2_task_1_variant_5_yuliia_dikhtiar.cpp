/*
  Назва задачі: Lab 2 Task 1
  Варіант: 5
  Автор: Діхтяр Юлія
  Група: ai-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const double epsilon = 0.0001;

    double sum = 0.0;
    double term = 1.0;
    double ratio = 0.0;

    int n = 1;

    while (fabs(term) > epsilon) {
        sum += term;
        ratio = -pow((double)n / (n + 1), n) / (n + 1);
        term *= ratio;
        n++;
    }

    cout << "Сума ряду: " << sum << endl;

    return 0;
}