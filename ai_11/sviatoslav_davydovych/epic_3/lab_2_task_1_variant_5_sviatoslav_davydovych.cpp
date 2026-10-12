/* Лабораторна робота N.2
Варіант: 5
Автор: Давидович Святослав
Група: ШІ-11 */

// не використовуємо cmath через повільну роботу pow для цілих чисел
#include <iostream>

using namespace std;

long long pow(int n, int k){
    long long m = 1;
    for (int i = 0; i<k;i++){
        m*=n;
    }
    return m;
}

// не рахуємо рекурентно, бо початкова формула з простою логікою ефективніша за рекуренте представлення
double sequence(int n){
    // замість піднесення (-1) у степінь, аналізуємо парність n-1
    if ((n-1)%2==0) return 1.0/pow(n,n); // операція ділення повертає double для нецілих
    else return -1.0/pow(n,n);
}

// e = 0.0001, a(n) = (-1)^(n-1)/n^n
int main() {
    constexpr double E = 0.0001; //точність

    double sum = 0,current;
    int n = 1;
    // do-блок гарантує, що умова в while коректно пройде першу ітерацію
    do {
        current = sequence(n);
        sum+=current;
        n++;
    } while (abs(current)>E);
    
    printf("Сума ряду з точністю 4 знаки після коми: %.4f\n",sum);
    return 0;
}