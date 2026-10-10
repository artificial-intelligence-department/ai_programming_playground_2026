/*
Аналізатор надійності пароля
Коваль Станіслав
СШІ-12
*/


#include <iostream>
using namespace std; 

int main() {
    //Ввід Pasword_length та перевірка
    int Pasword_length;
    cout << "Довжина паролю: ";
    cin >> Pasword_length;
    if (Pasword_length < 1 || Pasword_length > 64){
        cout << "Помилка: Пароль мусить мати більше 1 символа та менше 64" <<endl;
        return 1;
    }

    int symbols=0; 

    //Ввід numbers та перевірка
    char numbers;
    cout << "Чи є цифри (y/n): ";
    cin >> numbers;
    if (numbers != 'y' && numbers != 'n'){
        cout << "Помилка: Ввід має бути (y/n)" <<endl;
        return 1;
    }
    else if (numbers == 'y'){
        symbols++;
    }

    //Ввід uppercase_letters та перевірка
    char uppercase_letters;
    cout << "Чи є великі літери (y/n): ";
    cin >> uppercase_letters;
    if (uppercase_letters != 'y' && uppercase_letters != 'n'){
        cout << "Помилка: Ввід має бути (y/n)" <<endl;
        return 1;
    }
    else if (uppercase_letters == 'y'){
        symbols++;
    }

    //Ввід special_characters та перевірка
    char special_characters;
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special_characters;
    if (special_characters != 'y' && special_characters != 'n'){
        cout << "Помилка: Ввід має бути (y/n)" <<endl;
        return 1;
    }
    else if (special_characters == 'y'){
        symbols++;
    }

    //Перевірка на мінімальні вимоги
    if (Pasword_length < 8 || symbols < 2){
        cout << "Помилка: Мінімальні вимоги не виконано! " << endl;
    }
    
    //Перевірка який рівень надійності маєє твій пароль
    int level=0;
    if (Pasword_length < 6){
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
        level = 1;
    }
    else if (Pasword_length <= 8 || symbols==0){
        cout << "Рівень надійності: 2 - Слабкий" << endl;
        level = 2; 
    }
    else if (symbols==1){
        cout << "Рівень надійності: 3 - Середній" << endl;
        level = 3;
    }
    else if (Pasword_length >= 12 && symbols==3){
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
        level = 5;
    }
    else{
        cout << "Рівень надійності: 4 - Надійний" << endl;
        level = 4;
    }

    //Підказки за рівнем пароля
    switch (level) {
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

        default:
            cout << "Помилка. Пароль не підпадє під критерії" << endl;
            break;
    }

    //Перевірка чи пароль тільки з букв
    if (numbers != 'y' && special_characters != 'y'){
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
}