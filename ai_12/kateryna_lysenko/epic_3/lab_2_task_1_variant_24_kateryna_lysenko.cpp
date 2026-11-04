#include <iostream>
#include <cmath>
using namespace std;
double sum=0; // Змінна для накопичення суми членів ряду.
int main () {
    double sum=0;
    for(int n=1; n<=9; n++) { // цикл для зміни значення n від 1 до 9
        sum += exp( -sqrt(n));
    }
    cout << "Сума 9-ти членів ряду: " << sum << endl; // Вивод значення суми на екран
    return 0;
}