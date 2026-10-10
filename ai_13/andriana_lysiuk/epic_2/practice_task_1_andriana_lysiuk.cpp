#include <iostream>

using namespace std;
int main () {
    int length = 0;
    int reliability_level = 0;
    int types_count = 0;
    char digits = ' ';
    char uppercase = ' ';
    char special = ' ';

    //ввід і валідація
    cout << "Введіть довжину пароля: ";
    cin >> length;
    if (length > 64 || length < 1){
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }
    cout << "Чи є цифри (y/n): ";
    cin >> digits;
    if (digits != 'y' && digits != 'n'){
        cout << "Помилка: наявність цифр має бути y або n" << endl;
        return 1;
    }
    else if (digits == 'y'){
        types_count++;
    }
    cout << "Чи є великі літери (y/n): ";
    cin >> uppercase;
    if (uppercase != 'y' && uppercase != 'n'){
        cout << "Помилка: наявність великих літер має бути y або n" << endl;
        return 1;
    }
    else if (uppercase == 'y' ){
        types_count++;
    }
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special;
    if (special != 'y' && special != 'n'){
        cout << "Помилка: наявність спеціальних символів має бути y або n" << endl;
        return 1;
    }
    else if (special == 'y') {
        types_count++;
    }

    //мінімальні вимоги
    if (length >= 8 && types_count >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО " << endl;
    }
    else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО " << endl;
    }

    // рівень надійності
    if (length < 6){
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
        reliability_level = 1;
    }
    else if (length < 8 || types_count == 0){
        cout << "Рівень надійності: 2 - Слабкий" << endl;
        reliability_level = 2;
    }
    else if (types_count == 1){
        cout << "Рівень надійності: 3 - Середній" << endl;
        reliability_level = 3;
    }
    else if (length >= 12 && types_count == 3){
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
        reliability_level = 5;
    }
    else {
        cout << "Рівень надійності: 4 - Надійний" << endl;
        reliability_level = 4;
    }

    // рекомендація
    switch (reliability_level){
        case 1:
            cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
            break;
        default :
            return 1;
    }

    //попередження
    if (digits == 'n' && special == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше.";
    }
    return 0;
}
