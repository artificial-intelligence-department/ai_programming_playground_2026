#include <iostream>

using namespace std;

int main() {
    int n = 200;
    int sum = 0;
    // Цикл для обчислення чисел які діляться на 3 і їх додавання
    for (int i = 1; i < n; i++) {
        if (i % 3 == 0) {
            sum += i;
        }
    }
    cout << "Сума цілих додатніх чисел, кратних 3 та менших 200: " << sum << endl;
    
    return 0;
}
