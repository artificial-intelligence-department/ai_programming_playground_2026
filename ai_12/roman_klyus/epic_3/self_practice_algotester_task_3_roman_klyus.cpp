#include <iostream>
using namespace std;

int main() {
    int rows, columns;
    cin >> rows >> columns;

    int biggest[1000] = {0};

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            int number;
            cin >> number;

            // якщо це число більше за те, що ми запам'ятали для цього стовпця, оновлюємо
            if (number > biggest[column]) {
                biggest[column] = number;
            }
        }
    }

    // тепер серед найбільших чисел стовпців шукаємо найменше
    int answer = biggest[0];
    for (int column = 1; column < columns; column++) {
        if (biggest[column] < answer) {
            answer = biggest[column];
        }
    }

    cout << answer;
    return 0;
}