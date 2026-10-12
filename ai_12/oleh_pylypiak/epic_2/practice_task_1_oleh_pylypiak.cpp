#include <iostream>
using namespace std;

int main () {
    int length;
    char has_numbers;
    char has_capitals;
    char has_specials;
    // 1. Запитуємо вхідні данні у користувача
    cout << "Вкажіть довжину вашого пароля:";
    cin >> length;
    if (length<1 || length>64){
        cout << "Помилка! Довжина пароля повинна бути від 1 до 64 символів" << endl;
        return 0;
    }
    cout << "Чи містить ваш пароль цифри? (y/n):";
    cin >> has_numbers;
    if (has_numbers!='y' && has_numbers!='n'){
        cout << "Помилка! Введіть дійсне значення 'y' або 'n'" << endl;
        return 0;
    }
    cout << "Чи містить ваш пароль великі літери? (y/n):";
    cin >> has_capitals;
    if (has_capitals!='y' && has_capitals!='n'){
        cout << "Помилка! Введіть дійсне значення 'y' або 'n'" << endl;
        return 0;
    }
    cout << "Чи містить ваш пароль спеціальні символи? (y/n):";
    cin >> has_specials;
    if (has_specials!='y' && has_specials!='n'){
        cout << "Помилка! Введіть дійсне значення 'y' або 'n'" << endl;
        return 0;
    }
    // 2. Підраховуємо кількість типів символів у паролі
    int quantity = 0;
    if (has_numbers=='y') {quantity++;}
    if (has_capitals=='y') {quantity++;}
    if (has_specials=='y') {quantity++;}
    cout << "Кількість типів у вашому паролі:" << quantity << endl;
    // 3. Перевіряємо мінімальні вимоги
    cout << "Мінімальні вимоги:";
    if (length>8 && quantity>=2){
        cout << "Пройдено!" << endl;
    } else {
        cout << "Не пройдено(" << endl;
    }
    // 4. Визначаємо рівень безпеки пароля
    int lvl = 0;
    cout << "Рівень безпеки вашого пароля:";
    if (length<6){
        lvl = 1;
        cout << lvl << "(Дуже слабкий)" << endl;
    }
    else if ( length<8 || quantity==0) {
        lvl = 2;
        cout << lvl << "(Слабкий)" <<endl;
    }
    else if (quantity==1){
        lvl = 3;
        cout << lvl << "(Середній)" << endl;
    }
    else if (length>=12 && quantity==3){
        lvl = 5;
        cout << lvl << "(Дуже надійний)" << endl;
    }
    else {
        lvl = 4;
        cout << lvl << "(Надійний)" << endl;
    }
    // 5. Рекомендація
    cout << "Рекомендації щодо покращення безпеки:";
    switch(lvl){
        case 1:
        cout << " Пароль надто короткий. Мінімум 8 символів" << endl;
            break;
        case 2:
        cout << " Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи" << endl;
            break;
        case 3:
        cout << " Додайте ще один тип символів або збільште довжину до 12" << endl;
            break;
        case 4: 
        cout << " Хороший пароль. Для максимуму 12+ символів і всі три типи символів" << endl;
            break;
        case 5:
        cout << " Відмінно. Змінювати нічого не потрібно" << endl;
            break;
        default:
        cout << " Невідомий рівень безпеки пароля" << endl;
            break;
    }
    // 6. Попередження
    if (quantity==0 && length>=1 && length<=64){
        cout << "Попередження: пароль тільки з літер підбирається швидше" << endl;
    }
    return 0;
}