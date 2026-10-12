#include <iostream>

using namespace std;

int main() {
    int sum = 0;

    // перебираємо числа від 21 до 99
    for (int i = 21; i < 100; i++) {
        // беремо тільки ті, що діляться на 3
        if (i % 3 == 0) {
            sum += i;
        }
    }

    // результат
    cout << "Сума цілих додатних чисел, більших за 20, менших за 100 і кратних 3: "
        << sum << endl;

    return 0;
}
