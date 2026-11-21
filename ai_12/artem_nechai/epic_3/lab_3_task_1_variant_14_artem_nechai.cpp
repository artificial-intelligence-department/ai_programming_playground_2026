// Lab 3 Task 14

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

	const double pi = 3.141592653589793;
	const double pi_over_4 = pi / 4.0;

	// Задаємо константні значення з умови задачі
	const double epsilon = 0.0001;
	int n_max = 20;
	double a = pi / 5;
	double b = pi;
	const int k = 10;
	double x, value, sn, se, recursive, general, accurate_value;
	int n;

	// Формула для y = 1 / 4 * (x ^ 2 - pi ^ 2 / 3)
	// Формула Суми = (-1) ^ n * cos(n * x) / n ^ 2

	for (int i = 0; i <= k; i++) {
		// Обчислюємо значення x для поточного кроку i
		x = a + (b - a) / k * i;

		// Обчислюємо точне значення функції заданою формулою
		accurate_value = 1.0 / 4.0 * (pow(x, 2) - pow(pi, 2) / 3.0);

		sn = 0;
		// recursive = -1 бо (-1) ^ 0 = 1
		recursive = 1.0;

		for (n = 1; n <= n_max; n++) {
			// Обчислюємо (-1) ^ n на основі (-1) ^ (n - 1)
			recursive *= -1.0;

			// Обчислюємо n % 8 для визначення періодичності sin(n * pi / 4), 
			general = cos(n * x) / pow(n, 2);

			// Рахуємо значення n-го елемента прогресії
			value = recursive * general;

			// Додаємо відповідний елемент до суми
			sn += value;
		}

		se = 0;
		// recursive = -1 бо (-1) ^ 0 = 1
		recursive = 1.0;
		n = 0;
		do {
			n++;

			// Обчислюємо (-1) ^ n на основі (-1) ^ (n - 1)
			recursive *= -1.0;

			// Обчислюємо n % 8 для визначення періодичності sin(n * pi / 4), 
			general = cos(n * x) / pow(n, 2);

			// Рахуємо значення n-го елемента прогресії
			value = recursive * general;

			// Додаємо відповідний елемент до суми
			se += value;

		} while (abs(se - accurate_value) >= epsilon);

		cout << fixed << setprecision(7);
		cout << "X=" << x << "    SN=" << sn << "    SE=" << se << "    Y=" << accurate_value << endl;
	}

	return 0;
}