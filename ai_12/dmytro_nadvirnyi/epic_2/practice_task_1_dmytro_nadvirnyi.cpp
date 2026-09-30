#include <iostream>
using namespace std;

const int MAX_LENGTH = 64;

int main() {
    int level = 0;
    int type = 0;
    int length;
    char number;
    char capital;
    char special;

    cout << "Введіть довжину пароля: ";
    cin >> length;

    cout << "Введіть чи є цифри в паролі (y/n): ";
    cin >> number;

    cout << "Введіть чи є великі літери в паролі (y/n): ";
    cin >> capital;

    cout << "Введіть чи є спецсимволи в паролі (y/n): ";
    cin >> special;

    // Перевірка вводу
    if (length < 1 || length > MAX_LENGTH ||
        !(number == 'y' || number == 'n') ||
        !(capital == 'y' || capital == 'n') ||
        !(special == 'y' || special == 'n')) {

        cout << "Помилка вводу" << endl;
        return 1;
    }

    // Рахуємо кількість типів символів
    if (number == 'y') {
        type++;
    }

    if (capital == 'y') {
        type++;
    }

    if (special == 'y') {
        type++;
    }

    // Мінімальні вимоги
    if (length >= 8 && type >= 2) {
        cout << "ПРОЙДЕНО" << endl;
    }
    else {
        cout << "НЕ ПРОЙДЕНО" << endl;
    }

    // Визначення рівня
    if (length < 6) {
        level = 1;
    }
    else if (length < 8 || type == 0) {
        level = 2;
    }
    else if (type == 1) {
        level = 3;
    }
    else if (length >= 12 && type == 3) {
        level = 5;
    }
    else {
        level = 4;
    }

    // Рекомендація
    switch (level) {
    case 1:
        
        cout<< "  Рівень надійності: 1 - Дуже слабкий" <<endl;
        cout << "Пароль надто короткий. Мінімум 8 символів." << endl;
        break;


    case 2:
        
        cout<< "  Рівень надійності: 2 - Слабкий" <<endl;
        cout << "Збільште довжину до 8+ символів і додайте цифри, "
                "великі літери або спеціальні символи." << endl;
        break;

    case 3:
    
        cout<< "  Рівень надійності: 3 - Середній" <<endl;
        cout << "Додайте ще один тип символів або збільшіть довжину до 12." << endl;
        break;

    case 4:
    
        cout<< "  Рівень надійності: 4 - Надійний" <<endl;
        cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
        break;

    case 5:
        cout<< "  Рівень надійності: 5 - Дуже надійний" <<endl;
        cout << "Відмінно. Змінювати нічого не потрібно." << endl;
        break;

    default:
        cout << "Помилка рівня." << endl;
        break;
    }




    // Попередження: пароль без цифр (лише з літер) підбирається швидше
if (number == 'n') {
    cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
}

    return 0;
}