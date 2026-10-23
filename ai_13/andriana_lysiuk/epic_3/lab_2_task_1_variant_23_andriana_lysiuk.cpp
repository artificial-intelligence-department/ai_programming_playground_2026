/*
  Назва задачі: Lab 2 Task 1
  Варіант: 23
  Автор: Лисюк Андріана
  Група: ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    const int N = 10; // кількість членів ряду
    double a = 1.0; // a1 = 1
    double sum = a;

    for (int n = 1; n < N; n++) {
        a = a * (n + 1) * pow(n, sqrt (n)) / pow(n + 1, sqrt(n + 1));
        sum += a;
    }
    cout << "Сума 10 членів ряду = " << sum << endl;
    return 0;
}