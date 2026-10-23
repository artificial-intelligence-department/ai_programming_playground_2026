// Аналізатор місячного бюджету
#include <iostream>
#include <iomanip>

using namespace std;


const int max_days = 31;
const float day_limit_default = 1000;
const int top_spending_count = 3;


bool check_is_input_valid() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Помилка вводу. Спробуйте ще раз." << endl;
		return false;
	}
	return true;
}


void get_min_max(float* spending, int N, float* min_spending, float* max_spending) {
	*min_spending = spending[0];
	*max_spending = spending[0];
	for (int i = 1; i < N; i++) {
		if (spending[i] < *min_spending) {
			*min_spending = spending[i];
		}
		if (spending[i] > *max_spending) {
			*max_spending = spending[i];
		}
	}
}

float calc_sum_spending(float* spending, int i) {
	if (i == 0) {
		return spending[i];
	} else {
		return spending[i] + calc_sum_spending(spending, i-1);
	}
}



void menu_show_spending_on_days(float* spending, int N) {

	cout << left << setw(10) << "День" 
		<< right << setw(10) << "Витрати, грн" << endl;

	for (int i = 0; i < N; i++) {
		cout << left << setw(10) << "День " << (i + 1) << ": " 
			<< right << setw(10) << spending[i] << " грн" << endl;
	}
}


void menu_spending_statistic(float* spending, int N, float budget) {

	float min_spending, max_spending;
	get_min_max(spending, N, &min_spending, &max_spending);

	cout << left << setw(32) << "Мінімальні витрати за день: "
		<< right << setw(16) << min_spending << " грн" << endl
		<< left << setw(32) << "Максимальні витрати за день: "
		<< right << setw(16) << max_spending << " грн" << endl;

	float sum_spending = calc_sum_spending(spending, N - 1);

	cout << left << setw(32) << "Сумарні витрати: "
		<< right << setw(16) << sum_spending << " грн" << endl;

	if (sum_spending > budget) {
		float over_spending = abs(budget - sum_spending);
		cout << left << setw(32) << "Перевитрата понад бюджет: "
			<< right << setw(16) << over_spending << " грн" << endl;
	}

	int days_with_buys = 0;
	for (int i = 0; i < N; i++) {
		if (spending[i] == 0) {
			continue;
		}
		days_with_buys++;
	}

	float average_spending;
	if (sum_spending > 0) {
		average_spending = sum_spending / days_with_buys;
	}
	else {
		average_spending = 0;
	}

	cout << left << setw(32) << "Днів з покупками: "
		<< right << setw(16) << days_with_buys << endl
		<< left << setw(32) << "Середні витрати за такий день: "
		<< right << setw(16) << average_spending << " грн" << endl;

	int i = 0;
	sum_spending = 0;
	while (true) {
		sum_spending += spending[i];

		if (sum_spending > budget) {
			cout << "Бюджет вичерпано на дні " << i << ", накопичено: " << sum_spending << " грн." << endl;
			break;
		}

		i++;
		if (i == N) {
			cout << "Бюджету вистачило на всі дні, залишок: " << budget - sum_spending << " грн." << endl;
			break;
		}
	}
}


bool menu_days_with_over_limit(float* spending, int N) {
	cout << "Денний ліміт (грн, 0 - за замовчуванням(" << day_limit_default << " грн)): " << endl;

	float day_limit;
	cin >> day_limit;

	if (check_is_input_valid() == false) {
		return false;
	}

	if (day_limit == 0) {
		day_limit = day_limit_default;
	}
	cout << "Ліміт: " << day_limit << " грн" << endl;

    bool is_the_first_day_with_over_limit = true;
	int days_with_over_limit = 0;
	for (int i = 0; i < N; i++) {
		if (spending[i] > day_limit) {
            if (is_the_first_day_with_over_limit) {
                is_the_first_day_with_over_limit = false;
                cout << "Дні з перевищенням ліміту: " << endl;
            }

			cout << left << setw(12) << "  день " << i << ":" 
				<< right << setw(12) << spending[i] << " грн" << endl;
			days_with_over_limit++;
		}
	}
    if (days_with_over_limit == 0) {
	    cout << "Немає днів з перевищенням ліміту" << endl;
    } 
    else {
	    cout << "Разом днів з перевищенням: " << days_with_over_limit << endl;
    }

	return true;
}


void menu_top_spending_days(float spending[], int N) {
	for (int i = 1; i < N; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (spending[j] < spending[j+1]) {
				float temp = spending[j];
				spending[j] = spending[j+1];
				spending[j+1] = temp;
			}
		}
	}

	int top_spending_to_show_count;
	if (N > top_spending_count) {
		top_spending_to_show_count = top_spending_count;
	} else {
		top_spending_to_show_count = N;
	}

	cout << "Топ-" << top_spending_to_show_count << " витрат: ";
	for (int i = 0; i < top_spending_to_show_count; i++) {
		cout << spending[i] << ", ";
	}
	cout << "грн" << endl;
}





int main() {

	cout << "Бюджет на місяць (грн): ";
	float budget;
	do {
		cin >> budget;
	} while (check_is_input_valid() == false || budget <= 0);

	cout << "Кількість днів обліку: ";
	int N;
	while (true) {
		cin >> N;
		
		if (check_is_input_valid() == false) {
		} 
		else if (N <= 0) {
			cout << "Кількість днів має бути більша 0: ";
		} 
		else {
			break;
		}
	}

	cout << "Витрати по днях (грн): ";
	float spending[max_days];
	for (int i = 0; i < N; i++) {
		while (true) {
			cin >> spending[i];
			
			if (check_is_input_valid() == false) {
			} 
			else if (spending[i] < 0) {
				cout << "Значення витрат за день не може бути меншим за 0: ";
			} 
			else {
				break;
			}
		}
	}

	bool is_working = true;
	int action;

	// Меню
	menu:
		do {

			cout << "1 - Показати витрати по днях" << endl 
				<< "2 - Статистика витрат" << endl
				<< "3 - Дні з перевищенням денного ліміту" << endl
				<< "4 - Три найдорожчі дні" << endl
				<< "0 - Вийти" << endl;

			cin >> action;

			if (check_is_input_valid() == false) {
				goto menu;
			}

			switch (action) {
				case 1:
					menu_show_spending_on_days(spending, N);
					break;

				case 2:
					menu_spending_statistic(spending, N, budget);
					break;
					
				case 3:
					if (menu_days_with_over_limit(spending, N) == false) {
						goto menu;
					}
					break;

				case 4:
					menu_top_spending_days(spending, N);
					break;

				case 0:
					is_working = false;
			}

		} while (is_working);

	return 0;
}