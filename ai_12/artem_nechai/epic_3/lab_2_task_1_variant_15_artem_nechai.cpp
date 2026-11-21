// Lab 2 Task 1-15
#include <iostream>

using namespace std;

int main() {

	// Задаємо точність обчислень
	double epsilon = 0.0001;

	// Загальна формула для n-го елемента прогресії: (n! ^ 2) / (2 ^ n ^ 2)
	// Тому після підставлення 1 отримуємо:
	double value = 0.5;
	double sum = value;

	int n;
	for (n = 2; n <= 100; n++) {

		// За допомогою виведеної формули n+1-го елемента прогресії
		// обчислюємо його значення на основі n-го елемента прогресії
		value = value * n * n * pow(2, -(2 * n - 1));

		// Додаємо відповідний елемент до суми
		sum += value;

		// Перевіряємо, чи досягнуто заданої точності
		// Модуль відсутній, бо значення прогресії завжди додатне
		if (value < epsilon) {
			break;
		}
	}

	cout << "Progression sum: " << sum << endl;
	cout << "Progression exact sum: 0.829538" << endl;
	cout << "Used elements count: " << n << endl;

	return 0;
}