/* Плахтина Дмитро 
    ШІ-11
    Аналізатор надійності пароля
    Ви створюєте простий аналізатор надійності пароля. Користувач описує свій пароль, його довжину та які типи символів у ньому є, а програма визначає рівень надійності і видає рекомендацію, що саме варто виправити.
    Програма не зчитує сам пароль, а працює з його характеристиками.
*/
#include <iostream>
using namespace std;
int main() {
int length;
char isDigit;
char isBigLetter;
char isSpecialSymbol;
int level = 0;
// Введення даних про пароль
cout << "Введіть довжину пароля (від 1 до 64): ";
cin >> length;
if (length < 1 || length > 64) {
    cout << "Невірна довжина пароля" << endl;
    return 1;
}

cout << "Чи містить пароль цифру? (y/n): ";
cin >> isDigit;
if (isDigit != 'y' && isDigit != 'n') {
    cout << "Введіть лише 'y' або 'n'" << endl;
    return 1;
}

cout << "Чи містить пароль велику літеру? (y/n): ";
cin >> isBigLetter;
if (isBigLetter != 'y' && isBigLetter != 'n') {
    cout << "Введіть лише 'y' або 'n'" << endl;
    return 1;
}

cout << "Чи містить пароль спеціальний символ? (y/n): ";
cin >> isSpecialSymbol;
if (isSpecialSymbol != 'y' && isSpecialSymbol != 'n') {
    cout << "Введіть лише 'y' або 'n'" << endl;
    return 1;
}
// якщо кількість типів символів не менше двох то пароль проходить
if (length >= 8 && ((isDigit == 'y' && isBigLetter == 'y') || (isDigit == 'y' && isSpecialSymbol == 'y') || (isBigLetter == 'y' && isSpecialSymbol == 'y'))) {

    cout << "Пароль пройшов мінімальні вимоги" << endl;
} else {
    cout << "Пароль НЕ пройшов мінімальні вимоги" << endl;
}
// Визначення рівня надійності пароля
if (length < 6){
     level = 1;
    cout << "Рівень 1 - Дуже слабкий" << endl;
} else  if ((length >= 6 && length < 8) || (isDigit == 'n' && isBigLetter == 'n' && isSpecialSymbol == 'n')){
     level = 2;
    cout << "Рівень 2 - Слабкий" << endl;
} else if ( ((isDigit == 'y' && isBigLetter == 'n' && isSpecialSymbol == 'n') || (isDigit == 'n' && isBigLetter == 'y' && isSpecialSymbol == 'n') || (isDigit == 'n' && isBigLetter == 'n' && isSpecialSymbol == 'y'))){
     level = 3;
    cout << "Рівень 3 - Середній" << endl;
} else if (length >=12 && isDigit == 'y' && isBigLetter == 'y' && isSpecialSymbol == 'y'){
     level = 5;
    cout << "Рівень 5 - Дуже надійний" << endl;
} else {
     level = 4;
    cout << "Рівень 4 - Надійний" << endl;
}
// Виведення рекомендацій
switch (level)
{
    case 1: // Дуже слабкий
        cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
        break;
    case 2: // Слабкий
        cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
        break;
    case 3: // Середній
        cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
        break;
    case 4: // Надійний
        cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
        break;
    case 5: // Дуже надійний
        cout << "Відмінно. Змінювати нічого не потрібно." << endl;
        break;
    default: // Не мало б статися, якщо рівень визначено коректно
        cout << "Невідомий рівень надійності." << endl;
        break;
}
if (!(isDigit == 'y' || isSpecialSymbol == 'y')) {
    cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
}
    return 0;
}