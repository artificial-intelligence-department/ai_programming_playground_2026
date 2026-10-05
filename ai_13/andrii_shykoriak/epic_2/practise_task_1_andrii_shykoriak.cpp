#include <iostream>
using namespace std;
int main()
{
    // Ініціалізація змінних
    int pass_length,amout_of_types_characters,security_level;
    amout_of_types_characters = 0;
    cout << "Довжина пароля: ";
    cin >> pass_length;
    // Перевірка правильного вводку пароля
    if (pass_length > 64 || pass_length < 1){
        cout << "Помилка. Довжина пароля має бути від 1 до 64 символів";
        return 1;
    }
    // ініціалізація змінних потрібних визначення рівня захисту пароля та перевірка на вірність вводу
    string has_numbers,has_uppercase_letters,has_special_characters;
    cout << "Чи є цифри(y/n): ";
    cin >> has_numbers;
    if (has_numbers != "y" && has_numbers != "n"){
        cout << "Помилка. Відповідь має бути лише y або n";
        return 1;
    }
    if (has_numbers == "y"){
        amout_of_types_characters += 1;
    }
    cout << "Чи є великі літери(y/n): ";
    cin >> has_uppercase_letters;
    if (has_uppercase_letters != "y" && has_uppercase_letters != "n"){
        cout << "Помилка. Відповідь має бути лише y або n";
        return 1;
    }
    if (has_uppercase_letters == "y"){
        amout_of_types_characters += 1;
    }
    cout << "Чи є спеціальні символи(y/n): ";
    cin >> has_special_characters;
    if (has_special_characters != "y" && has_special_characters != "n"){
        cout << "Помилка. Відповідь має бути лише y або n";
        return 1;
    }
    if (has_special_characters == "y"){
        amout_of_types_characters += 1;
    }
    // Визначення рівня надійності
    if (pass_length < 6){
        security_level = 1;
    }
    else if (pass_length < 8 || amout_of_types_characters == 0 ){
        security_level = 2;
    }
    else if (amout_of_types_characters == 1){
        security_level = 3;
    }
    else if (pass_length >= 12 && amout_of_types_characters == 3){
        security_level = 5;
    }
    else {
        security_level = 4;
    }
    // Ініціалізація і перевірка на виконання мінімальних вимог
    bool min_demands;
    if (pass_length >= 8 && amout_of_types_characters >= 2){
        min_demands = true;
    }
    else{
        min_demands = false;
    }
    cout << "\n";
    
    if (!min_demands){
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }
    else{
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    // Виведення результатів залежно від рівня надійності
    switch(security_level){
        case 1:
            cout << "Рівень надійності: 1 - Дуже слабкий" << endl << "Рекомендація: Пароль надто короткий. Мінімум 8 символів."<<endl;
            break;
        case 2:
            cout << "Рівень надійності: 2 - Слабкий" << endl << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<<endl;
            break;
        
        case 3:
            cout << "Рівень надійності: 3 - Середній" << endl << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12."<<endl;
            break;
        case 4:
            cout << "Рівень надійності: 4 - Надійний" << endl << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів"<<endl;
            break;
        case 5:
            cout << "Рівень надійності: 5 - Дуже надійний" << endl << "Рекомендація: Відмінно. Змінювати нічого не потрібно."<<endl;
            break;
        default:
            cout << "Помилка визначення надійності";
        
    }
    if (has_numbers == "n" && has_special_characters == "n"){
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
    return 0;
}