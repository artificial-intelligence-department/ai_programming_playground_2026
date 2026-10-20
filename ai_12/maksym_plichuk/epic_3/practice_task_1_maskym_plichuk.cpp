#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/* Практична робота: Аналізатор місячного бюджету
 Плічук Максим ШІ-12*/

void showSpentByDays(double spending[], int size) {
	cout << "\nДень\tВитрати, грн\n";
	for (int i = 0; i < size; i++) {
		cout << setw(4) << i + 1 << setw(17) << fixed << setprecision(2) << spending[i] << endl;
	}
};

void getMinMax(double spending[], int size, double& min, double& max) {
	min = max = spending[0];
	for (int i = 0; i < size; i++)
	{
		if (spending[i] > max) max = spending[i];
		if (spending[i] < min) min = spending[i];
	}
}

double totalSpent(double spending[], int size) {
	if (size == 0) return 0.0;
	return spending[size - 1] + totalSpent(spending, size - 1);
}

void spendingStats(double spending[], int size, int budget) {

	double min = 0;
	double max = 0;
	getMinMax(spending, size, min, max);

	cout << "\nМінімальні витрати за день: " << min << endl;
	cout << "Максимальні витрати за день: " << max << endl;

	double total = totalSpent(spending, size);
	cout << "Сумарні витрати: " << total << endl;

	double remainings = budget - total;
	if (remainings < 0) {
		cout << "Перевитрата понад бюджет: " << fabs(remainings) << endl;
	}
	else {
		cout << "Залишок бюджету: " << remainings << endl;
	}

	int daysWithSpending = 0;
	for (int i = 0; i < size; i++)
	{
		if (spending[i] == 0) continue;
		daysWithSpending++;
	}
	cout << "Днів з покупками " << daysWithSpending << endl;
	cout << "Середні витрати за такий день: " << (daysWithSpending == 0 ? 0.0 : total / daysWithSpending) << endl;

	double spent = 0;
	int day = 0;
	int dayWhenBudgetEnded = -1;
	while (day < size){
		spent += spending[day];
		if (spent > budget) {
			dayWhenBudgetEnded = day;
			break;
		}
		day++;
	}
	if (dayWhenBudgetEnded!=-1)
	{
		cout << "Бюджет вичерпано на дні " << dayWhenBudgetEnded+1 << ", накопичено " << spent << " грн. "<< endl;
	}else {
		cout << "Залишок після всіх днів: " << budget - spent << endl;
	}

};

void daysOverLimit(double spending[], int size, double limit = 1000) {
	if (limit == 0) limit = 1000;

	int count = 0;
	cout << "Ліміт: " << limit << endl;
	for (int i = 0; i < size; i++)
	{
		if (spending[i] > limit)
		{
			cout << "\tдень " << i+1 << " " << spending[i] << " грн" << endl;
			count++;
		}
	}
	cout << "Разом днів з перевищенням: " << count << endl;
};

void top3MostExpensive(double spending[], int& size) {
	cout << "Топ-3 витрат: ";
	double sortedArr[size] = {0};
	for (int i = 0; i < size; i++)
	{
		sortedArr[i] = spending[i];
	}
	

	for (int i = 0; i < size-1; i++)
	{
		int maxIndex = i;
		for (int j = i+1; j < size; j++)
		{
			if (sortedArr[j]>sortedArr[maxIndex])
			{
				maxIndex = j;
			}
		}
		double temp = sortedArr[i];
		double b = sortedArr[maxIndex];
		sortedArr[i] = b;
		sortedArr[maxIndex] = temp;
	}

	for (int i = 0; i < size; i++)
	{
		cout << sortedArr[i] << ((i==2 || i==size-1)? " грн" : ", ");
		if (i==2 || i==size-1) break;
	}
	cout << endl;
};


int main()
{
	const int MAX_DAYS = 31;

	int budget;
	cout << "Бюджет на місяць (грн): ";
	while (!(cin>>budget) || budget < 1){
		cout << "Введіть правильне значення бюджету (>0): ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	int N;
	cout << "Кількість днів обліку: ";
	while (!(cin >> N) || N < 1 || N > MAX_DAYS) {
		cout << "Введіть правильне значення днів обліку (1-31): ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	double spending[N];
	cout << "Витрати по днях (грн): ";
	for (int i = 0; i < N; i++) {
		while (!(cin >> spending[i]) || spending[i] < 0) {
			cout << "Введіть правильне значення витрати за " << i+1 << " день: ";
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	int input_choice;
	double limit = 0;
	do {

	menu:
		cout << "\nМеню:" << endl;
		cout << "1. Показати витрати по днях" << endl;
		cout << "2. Статистика витрат" << endl;
		cout << "3. Дні з перевищенням денного ліміту" << endl;
		cout << "4. Три найдорожчі дні" << endl;
		cout << "0. Вийти" << endl;
		cout << "Виберіть пункт меню: ";

		if (!(cin >> input_choice) || input_choice > 4 || input_choice < 0) {
			cout << "Неправильний пункт меню!" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			goto menu;
		}

		switch (input_choice){
		case 1:
			showSpentByDays(spending, N);
			break;
		case 2:
			spendingStats(spending, N, budget);
			break;
		case 3:
			cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
			while (!(cin >> limit) || limit < 0) {
				cout << "Введіть правильне значення ліміту (>0): " << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
			daysOverLimit(spending, N, limit);
			break;
		case 4:
			top3MostExpensive(spending, N);
			break;
		case 0:
			cout << "Вихід....";
			break;
		default:
			break;
		}

	} while (input_choice != 0);

}
