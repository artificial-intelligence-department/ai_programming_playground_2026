/*
Епік 2. Практичне завдання: Аналізатор надійності пароля
Грабовенський Кирило
СШІ-13
*/
#include <iostream>

using namespace std;
int main()
{
	// =========================================================================
	// СТРУКТУРНИЙ БЛОК 1: ВВЕДЕННЯ ДАНИХ ТА ВАЛІДАЦІЯ ДОВЖИНИ ПАРОЛЯ
	// =========================================================================
	cout << "enter length of your password\n";

	int length;
	cin >> length;

	if (length > 64)
	{
		cout << "your password is too big";
		return 1;
	}
	else
	{
		if (length <= 0)
		{
			cout << "it can't be serious it can't be like that";
			return 1;
		}
	}

	// =========================================================================
	// СТРУКТУРНИЙ БЛОК 2: ІНТЕРАКТИВНЕ ОПИТУВАННЯ ТА КОНВЕРТАЦІЯ ТИПІВ ДАНИХ
	// (Збір відповідей користувача у форматі 'y'/'n' та їх перевірка через switch)
	// =========================================================================

	// Перевірка надійності: наявність цифр
	cout << "does your password have any numbers?(y/n)\n";
	char numbersw;
	cin >> numbersw;
	bool numbers;
	switch (numbersw)
	{
	case 'y': numbers = 1; break;
	case 'n': numbers = 0; break;
	default:  cout << "you have to write y or n only"; return 1; break;
	}

	// Перевірка надійності: наявність великих літер
	cout << "does your password have any big letter?\n";
	char big_letterw;
	cin >> big_letterw;
	bool big_letter;
	switch (big_letterw)
	{
	case 'y': big_letter = 1; break;
	case 'n': big_letter = 0; break;
	default:  cout << "you have to write y or n only"; return 1; break;
	}

	// Перевірка надійності: наявність спеціальних символів
	cout << "does your password contain charter word?\n";
	char charter_wordw;
	cin >> charter_wordw;
	bool charter_word;
	switch (charter_wordw)
	{
	case 'y': charter_word = 1; break;
	case 'n': charter_word = 0; break;
	default:  cout << "you have to write y or n only"; return 1; break;
	}

	// =========================================================================
	// СТРУКТУРНИЙ БЛОК 3: ЛОГІЧНЕ ЯДРО (ОБЧИСЛЕННЯ РІВНЯ БЕЗПЕКИ ВІД 1 ДО 5)
	// (Аналіз довжини та комбінацій прапорців за допомогою каскаду умов if-else)
	// =========================================================================
	int level_of_security;

	if (length < 6)
	{
		level_of_security = 1;
	}
	else
	{
		if (length < 8 || (!numbers && !big_letter && !charter_word))
		{
			level_of_security = 2;
		}
		else
		{
			int nods = numbers + big_letter + charter_word;

			if (nods == 1)
			{
				level_of_security = 3;
			}
			else
			{
				if (length >= 12 && nods == 3)
				{
					level_of_security = 5;
				}
				else
				{
					level_of_security = 4;
				}
			}
		}
	}

	// =========================================================================
	// СТРУКТУРНИЙ БЛОК 4: ФІНАЛЬНЕ ВИВЕДЕННЯ РЕЗУЛЬТАТІВ ТА РЕКОМЕНДАЦІЙ
	// (Формування текстового вердикту на основі визначеного рівня безпеки)
	// =========================================================================
	switch (level_of_security)
	{
	case(1):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "it is not enought\n";
		cout << "it is too short it should have at least 8 symbols";
		break;

	case(2):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "it is not enought\n";
		cout << "make at least 8 symbols and add numbers, big letters or special characters.";
		break;

	case(3):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "it is not enought\n";
		cout << "add another type of symbol and make it a bit longer at least 12.";
		break;

	case(4):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "It is a nise password but add 12 symbols and all 3 type of symbols.";
		break;

	case(5):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "Amasing. it is perfect.";
		break;
	}
}