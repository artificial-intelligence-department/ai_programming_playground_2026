/* 
Задача: Algotester Self-Practice №1.
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
using namespace std;

int main() {

int n = 0;
int k = 0;
int a[10000001] = {0};
int count = 1;
int c[10000001] = {0};
int max = 0;
cin >> n >> k;
for (int i = 0; i < n; i++) {
    cin >> a[i];
}
for (int i = 0; i < n; i++) {
    if (a[i] >= k) { //перевірка зубів на гостроту
c[i] = count++;}//записуємо +1 до кількості гострих підряд
    if (a[i] < k) count = 1; //якщо не гострий, то скидаємо кількість гострих підряд до одинички
}
for (int i = 0; i < n; i++) {
    if (max <= c[i]) max = c[i]; //шукаємо максимум
    if (max > c[i]) max = max; 
}

cout << max;

    return 0;
}