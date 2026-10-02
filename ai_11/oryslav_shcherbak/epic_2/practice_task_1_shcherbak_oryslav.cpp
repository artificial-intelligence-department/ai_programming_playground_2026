#include <iostream>
#include <string>
using namespace std;
/* Задача: Practice task 1
 * Щербак Орислав
 * Група ШІ - 11
 */
int main() {
    // оголошення змінних
    int length;
    char digits;
    char uppersymbols;
    char specialsymbols;
    // введення даних користувачем та перевірка на коректність  
    cout << "Довжина пароля: ";
    if (!(cin >> length) || length < 1 || length > 64) {
        cout << "Довжина пароля повинна бути від 1 до 64 символів." << endl;
        return 1;
    }
    cout << "Чи є цифри (y/n): ";
    cin >> digits;
    if(digits != 'y' && digits != 'n') {
        cout << "Помилка, введіть 'y' або 'n'." << endl;
        return 1;
    }
    cout<< "Чи є великі літери (y/n): ";
    cin >> uppersymbols;
    if(uppersymbols != 'y' && uppersymbols != 'n') {
        cout << "Помилка, введіть 'y' або 'n'." << endl;
        return 1;
    }
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> specialsymbols;
    if(specialsymbols != 'y' && specialsymbols != 'n') {
        cout << "Помилка, введіть 'y' або 'n'." << endl;
        return 1;
    }
    // перетворення введених символів у bool
    bool hasdigits = digits == 'y';
    bool hasupper = uppersymbols == 'y';
    bool hasspecial = specialsymbols == 'y';
    // кількість типів символів
    int types = 0;
    if (hasdigits) types++;
    if (hasupper) types++;
    if (hasspecial) types++;
    // перевірка мінімальних вимог
    if (length < 8 || types < 2) {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    // визначення рівня надійності
    int level; 
    string levelStr;
    if (length < 6){
        level = 1;
        levelStr = "1 - Дуже слабкий";
    } else if (length < 8 || types == 0) {
        level = 2;
        levelStr = "2 - Слабкий";
    } else if (types ==1) {
        level = 3;
        levelStr = "3 - Середній";
    } else if (length >= 12 && types == 3) {
        level = 5;
        levelStr = "5 - Дуже надійний";
    } else {
        level = 4;
        levelStr = "4 - Надійний";
    }
    cout << "Рівень надійності: " << levelStr << endl;
    // рекомендації щодо покращення надійності
    switch(level) {
        case 1:
            cout << "Рекомендації: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Рекомендації: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Рекомендації: Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Рекомендації: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Рекомендації: Відмінно. Змінювати нічого не потрібно." << endl;
            break;
        default:
            cout << "Помилка визначення надійності." << endl;
            return 1;
    }
    // додаткове попередження, якщо пароль складається тільки з літер
    if (!hasdigits && !hasspecial) {
        cout << "Попередження: Пароль тільки з літер підбирається швидше." << endl;
    }
    return 0;
    }