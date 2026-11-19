// Lab 4 Task 1 Variant 23
#include <iostream>

using namespace std;

void input_again(int &a) {
	cin.clear();
	cin.ignore(256, '\n');
	cout << "Неправильний ввід, спробуйте ще раз: ";
	cin >> a;
}

int main() {
	int a[100];
	
	cout << "Введіть кількість елементів масиву: ";
	int n;
	cin >> n;
	while (cin.fail() || n < 1 || n > 100) {
		input_again(n);
	}

	cout << "Введіть елементи масиву: ";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		while (cin.fail()) {
			input_again(a[i]);
		}
	}

	cout << "Введіть число K: ";
	int k;
	cin >> k;
	while (cin.fail() || k < 1 || k > n) {
		input_again(k);
	}

	// Змінення k на -1 для звичайної індексації елементів масиву
	k -= 1;

	// Вивід елементів k до k-1
	for (int i = 0; i < n; i++) {
		cout << a[(k - i + n) % n] << " ";
	}
	cout << endl;

	// Знищення з кільця всіх елементів що співпадають з максимальним елементом
	
	// Пошук найбільшого
	int max_value = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > max_value) {
			max_value = a[i];
		}
	}

	// Оновлення масиву без елементів що співпадають з максимальним
	int add_element_index = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] != max_value) {
			a[add_element_index] = a[i];
			add_element_index++;
		}
	}

	// Оскільки масив перезаписаний без деяких елементів,
	// то його нова довжина є кількістю елементів які ми записали
	n = add_element_index;

	// Вивід елементів з k до k+1
	for (int i = 0; i < n; i++) {
		cout << a[(k + i) % n] << " ";
	}
	cout << endl;
	

	return 0;
}