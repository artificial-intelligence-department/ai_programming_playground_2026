/*
Аналізатор надійності пароля
Цебуля Вадим
ШІ - 12
*/


#include <iostream>
using namespace std;
int main() {
        // Введення довжини пароля та перевірка допустимого діапазону (1-64)
        int password_length;
        cout << "Введіть довжину пароля: ";
        cin >> password_length;
        if (!(password_length >= 1 && password_length <= 64) ){
                cout << "Помилка: довжина пароля мусить бути від 1 до 64." << endl;
                return 1;
        }

        // Перевіряємо наявність цифр у паролі
        char digits;
        cout << "Чи є цифри (y/n): ";
        cin >> digits;
        if (!(digits == 'y' || digits == 'n')){
                cout << "Помилка: ввід має бути 'y' або 'n'" << endl;
                return 1;
        }

        // Перевіряємо наявність великих літер
        char uppercase;
        cout << "Чи є великі літери (y/n): ";
        cin >> uppercase;
        if (!(uppercase == 'y' || uppercase == 'n')){
                cout << "Помилка: ввід має бути 'y' або 'n'" << endl;
                return 1;
        }

        // Перевіряємо наявність спеціальних символів
        char specialsymbols;
        cout << "Чи є спеціальні символи (y/n): ";
        cin >> specialsymbols;
        if (!(specialsymbols == 'y' || specialsymbols == 'n')){
                cout << "Помилка: ввід має бути 'y' або 'n'" << endl;
                return 1;
        }


        // Підрахунок кількості обраних типів символів
        int types_count = 0;
        if (digits == 'y') 
        types_count++;
        
        if (uppercase == 'y') 
        types_count++;
        
        if (specialsymbols == 'y') 
        types_count++;

        // Перевірка мінімальних вимог (довжина від 8 символів і мінімум 2 типи символів)
        if (password_length >= 8 && types_count >= 2)
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
        else 
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;


        // Визначення рівня надійності пароля (1-5)
        int lvl = 0;

        if (password_length < 6) {
                lvl = 1;
                cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
        }
        else if (password_length < 8 || types_count == 0) {
                lvl = 2;
                cout << "Рівень надійності: 2 - Слабкий" << endl;
        }
        else if (types_count == 1) {
                lvl = 3;
                cout << "Рівень надійності: 3 - Середній" << endl;
        }
        else if (password_length >= 12 && types_count == 3) {
                lvl = 5;
                cout << "Рівень надійності: 5 - Дуже надійний" << endl;
        }
        else {
                lvl = 4;
                cout << "Рівень надійності: 4 - Надійний" << endl;
        }

        // Надання поради користувачеві залежно від отриманого рівня (lvl)
        switch(lvl){
                case 1: cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl; break;
                case 2: cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<< endl; break;
                case 3: cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl; break;
                case 4: cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl; break;
                case 5: cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl; break;

                default: cout << "Помилка: неможливо визначити рівень безпеки пароля." << endl; break;
        }

        // Окреме застереження, якщо пароль складається виключно з літер
        if (digits == 'n' && specialsymbols == 'n')
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;

        return 0;
}



