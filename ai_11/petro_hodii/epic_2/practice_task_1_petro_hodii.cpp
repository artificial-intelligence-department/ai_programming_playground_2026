#include <iostream>

using namespace std;

int main(){
    //Створюю змінні
    int length, numOfSym, numOfCase;
    char isNumber, isCapLetter, isSpecSym;

    //Введення змінних
    cout << "Довжина пароля: ";
    cin >> length;
    if(length <= 0 || length > 64){
        cout << "Помилка: довжина мусить бути від 1 до 64.\n";
        return 1;
    }
    cout << "Чи є цифри (y/n): ";
    cin >> isNumber;
    if(isNumber != 'y' && isNumber != 'n'){
        cout << "Помилка: введіть лише y або n\n";
        return 1;
    }
    cout << "Чи є великі літери (y/n): ";
    cin >> isCapLetter;
    if(isCapLetter != 'y' && isCapLetter != 'n'){
        cout << "Помилка: введіть лише y або n\n";
        return 1;
    }
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> isSpecSym;
    if(isSpecSym != 'y' && isSpecSym != 'n'){
        cout << "Помилка: введіть лише y або n\n";
        return 1;
    }

    //Перевірка скільки типів символів є
    if(isNumber == 'y'){
        numOfSym++;
    }
    if(isCapLetter == 'y'){
        numOfSym++;
    }
    if(isSpecSym == 'y'){
        numOfSym++;
    }

    //Перевірка чи проходить пароль мінімальні вимоги
    if(length >= 8 && numOfSym >= 2){
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else{
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    //Перевірка рівня надійності пароля і виведення результату в консоль
    if(length < 6){
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
        numOfCase = 1;
    }
    else if(length < 8 || numOfSym == 0){
        cout << "Рівень надійності: 2 - Слабкий" << endl;
        numOfCase = 2;
    }
    else if(numOfSym == 1){
        cout << "Рівень надійності: 3 - Середній" << endl;
        numOfCase = 3;
    }
    else if(length >= 12 && numOfSym == 3){
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
        numOfCase = 5;
    }
    else{
        cout << "Рівень надійності: 4 - Надійний" << endl;
        numOfCase = 4;
    }

    //Виведення рекомендацій
    switch(numOfCase){
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно." << endl;
            break;
    }

    //Перевірка чи треба виводити попередження
    if(numOfSym == 0 || (isCapLetter == 'y' && numOfSym == 1)){
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}