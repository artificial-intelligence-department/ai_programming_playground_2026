/* Плахтина Дмитро
   ШІ-11
   Знайти суму цілих додатніх чисел, більших 20, менших 100 і кратних 3*/
#include <iostream>
using namespace std;

int main() {
int sum = 0;
for (int i = 20; i < 100; i++) {
    if (i % 3 == 0) {sum += i;}
}
cout << "Сума цілих додатніх чисел від 20 до 100 і кратних 3 = " << sum;

    return 0;
}