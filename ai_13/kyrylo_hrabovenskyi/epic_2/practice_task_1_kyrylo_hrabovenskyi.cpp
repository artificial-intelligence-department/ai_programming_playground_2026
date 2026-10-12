/*
Епік 2. Практичне завдання: Аналізатор надійності пароля
Грабовенський Кирило
СШІ-13
*/
#include <iostream>

using namespace std;
int main()
{
	//ініціалізація отримання і перевірка довжини пароля

	cout << "enter length of your password\n"; // Запит користувачу ввести довжину пароля

	int length; // Змінна для збереження довжини пароля

	cin >> length; // Зчитування довжини з клавіатури

	if (length > 64) // Перевірка, чи не перевищує довжина максимальну межу
	{

		cout << "your password is too big"; // Повідомлення про занадто довгий пароль

		return 1; // Завершення програми з кодом помилки
	}
	else
	{

		if (length <= 0) // Перевірка на некоректну або нульову довжину
		{
			cout << "it can't be serious it can't be like that"; // Повідомлення про неможливе значення

			return 1; // Завершення програми з кодом помилки
		}
	}

	//перевірка на наявність цифр

	cout << "does your password have any numbers?(y/n)\n"; // Запит про наявність цифр у паролі

	char numbersw; // Змінна для збереження символу-відповіді (y/n)

	cin >> numbersw; // Зчитування відповіді користувача

	bool numbers; // Логічний прапорець наявності цифр

	switch (numbersw) // Аналіз відповіді про цифри за допомогою switch
	{

	case 'y':
		numbers = 1; // Якщо 'y', встановлюємо істину (true)
		break;

	case 'n':
		numbers = 0; // Якщо 'n', встановлюємо хибність (false)
		break;

	default:
		cout << "you have to write y or n only"; // Обробка некоректного введення
		return 1; // Завершення програми в разі помилки введення
		break;
	}

	//перевірка на наявність великих літер

	cout << "does your password have any big letter?\n"; // Запит про наявність великих літер

	char big_letterw; // Змінна для збереження символу-відповіді (y/n)

	cin >> big_letterw; // Зчитування відповіді

	bool big_letter; // Логічний прапорець наявності великих літер

	switch (big_letterw) // Аналіз відповіді про великі літери
	{

	case 'y':
		big_letter = 1; // Якщо 'y', встановлюємо true
		break;

	case'n':
		big_letter = 0; // Якщо 'n', встановлюємо false
		break;

	default:
		cout << "you have to write y or n only"; // Обробка помилки введення
		return 1; // Завершення програми
		break;

	}

	//перевірка на наявність спеціальних символів

	cout << "does your password contain charter word?\n"; // Запит про наявність спеціальних символів

	char charter_wordw; // Змінна для збереження відповіді (y/n)

	cin >> charter_wordw; // Зчитування відповіді

	bool charter_word; // Логічний прапорець наявності спецсимволів

	switch (charter_wordw) // Аналіз відповіді про спецсимволи
	{

	case 'y':
		charter_word = 1; // Якщо 'y', встановлюємо true
		break;

	case 'n':
		charter_word = 0; // Якщо 'n', встановлюємо false
		break;

	default:
		cout << "you have to write y or n only"; // Обробка помилки введення
		return 1; // Завершення програми
		break;

	}

	//визначення рівня надійності

	int level_of_security; // Змінна для збереження розрахованого рівня безпеки

	if (length < 6) // Якщо довжина менша за 6 символів
	{
		level_of_security = 1; // Рівень надійності 1 (найнижчий)
	}
	else
	{

		// Якщо довжина менша за 8 АБО не вибрано жодного додаткового типу символів
		if (length < 8 || (!numbers && !big_letter && !charter_word))
		{
			level_of_security = 2; // Рівень надійності 2
		}
		else
		{

			// Рахуємо суму підтверджених типів символів (значення bool неявно приводяться до 0 або 1)
			int nods = numbers + big_letter + charter_word;

			if (nods == 1) // Якщо присутній лише 1 додатковий тип символів
			{
				level_of_security = 3; // Рівень надійності 3
			}
			else
			{
				// Якщо довжина від 12 символів і присутні всі 3 додаткові типи
				if (length >= 12 && nods == 3)
				{
					level_of_security = 5; // Рівень надійності 5 (найвищий, ідеальний)
				}
				else
				{
					level_of_security = 4; // В усіх інших випадках рівень надійності 4
				}
			}
		}
	}

	//виведення рекомендації щодо відповідного рівня

	switch (level_of_security) // Вибір повідомлення залежно від визначеного рівня безпеки
	{
	case(1):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "it is not enought\n";
		cout << "it is too short it should have at least 8 symbols"; // Рекомендація для рівня 1
		break;

	case(2):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "it is not enought\n";
		cout << "make at least 8 symbols and add numbers, big letters or special characters."; // Рекомендація для рівня 2
		break;

	case(3):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "it is not enought\n";
		cout << "add another type of symbol and make it a bit longer at least 12."; // Рекомендація для рівня 3
		break;

	case(4):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "It is a nise password but add 12 symbols and all 3 type of symbols."; // Рекомендація для рівня 4
		break;

	case(5):
		cout << "yor level of password is " << level_of_security << endl;
		cout << "Amasing. it is perfect."; // Похвала для рівня 5
		break;
	}
}