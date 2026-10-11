/*  
Аналізатор надійності паролю
Автор: Мадяр Андрій
Група: ШІ-13
*/
#include <iostream>
using namespace std;
int main() {
    // створюю змінні-характеристики пароля які буду перевіряти
    int length = 0, level = 0 , specials = 0;
    char Digit = 0, Uppercase = 0, spSymbol = 0;
    bool minReq = 0;
    // введення довжини пароля
    cout << "довжина пароля: ";
    cin >> length;
    //перевірка умов по довжині
    if(length < 1 || length > 64) {
        cout << "довжина пароля має бути від 1 до 64 символів" << endl;
        return 1;
    }
    //введення змінних які будуть харакитеризувати перевірку завдяки specials, водночас з перевіркою на правильне введення
    //введення чи є цифри
    cout << "є цифри?(y/n): ";
    cin >> Digit;
    //перевірка
    if(Digit != 'y' && Digit != 'n') {
        cout << "неправильне введення, має бути y чи n" << endl;
        return 1;
    }
    //введення чи є великі літери
    cout << "є великі літери?(y/n): ";
    cin >> Uppercase;
    //перевірка
    if(Uppercase != 'y' && Uppercase != 'n') {
        cout << "неправильне введення, має бути y чи n" << endl;
        return 1;
    }
    //введення чи є спеціальні символи
    cout << "є спеціальні символи?(y/n): ";
    cin >> spSymbol;
    //перевірка
    if(spSymbol != 'y' && spSymbol != 'n') {
        cout << "неправильне введення, має бути y чи n" << endl;
        return 1;
    }
    //підрахунок особливостей(типів?) у паролі
    if(Digit == 'y') {
        specials++;
    }
    if(Uppercase == 'y') {
        specials++;
    }
    if(spSymbol == 'y') {
        specials++;
    }   
    //перевірка на мінімальні вимоги
    if(length >= 8 && specials >= 2) {
        minReq = true;
    }else {
        minReq = false;
    }
    //визначення рівня надійності пароля
    if(length < 6) {
        level = 1;
    }else if(length < 8 || specials == 0){
        level = 2;
    }else if(specials == 1){
        level = 3;
    }else if (length >= 12 && specials == 3) {
        level = 5;
    }else {
        level = 4;
    }
    // вивід чи пройшов мінімальні вимоги
    if(minReq == true) {
        cout << "мінімальні вимоги: ПРОЙДЕНО" << endl;
    }else {
        cout << "мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }
    // вивід назви рівня надійності пароля
    if (level == 1) {
        cout << "рівень надійності: 1 - Дуже слабкий" << endl;
    }else if (level == 2) {
        cout << "рівень надійності: 2 - Слабкий" << endl;
    }else if (level == 3) {
        cout << "рівень надійності: 3 - Середній" << endl;
    }else if (level == 4) {
        cout << "рівень надійності: 4 - Надійний" << endl;
    }else if (level == 5) {
        cout << "рівень надійності: 5 - Дуже надійний" << endl;
    }
    //вивід рекомендації використовуючи switch
    cout << "рекомендація: ";
    switch (level) {
        case 1: cout << "Пароль надто короткий. Мінімум 8 символів." << endl; break;
        case 2: cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl; break;
        case 3: cout << "Додайте ще один тип символів або збільште довжину до 12." << endl; break;
        case 4: cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl; break;
        case 5: cout << "Відмінно. Змінювати нічого не потрібно." << endl; break;
        default: cout << "рівень надійності не визначений" << endl; break;
    }
    //попередження якщо в паролі є лише малі літери
    if (specials == 0) {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
    return 0;
}
