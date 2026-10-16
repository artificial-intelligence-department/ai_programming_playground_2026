
/*
    Lab 2, Рубаха Олексій, ШІ-13, Варіант 2
*/

#include <iostream>

using namespace std;

int main() {
    int sum = 0;

    for (int i = 2; i < 100; i += 2) {
        sum += i;
    }

    cout << "Сума додатних парних цілих чисел, менших 100: " << sum << endl;

    return 0;
}
