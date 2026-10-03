/*
Аналізатор надійності пароля
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    int p_length;
    cout << "Довжина пароля: ";
    cin >> p_length;
    if (p_length < 1 || p_length > 64) {
        cout << "Помилка: довжина має бути від 1 до 64. " << endl;
        return 1;
    }

    char has_num;
    cout << "Чи є цифри (y/n): ";
    cin >> has_num;
    if (!(has_num == 'y' || has_num == 'n')){ 
        cout << "Помилка: дозволено тільки y або n." << endl;
        return 1;
    }
    // ! - заперечення. Тут використовується закон Деморгана ! пристусовується до кожної змінної, а || змінюється на &&
    

    char has_capital_l;
    cout << "Чи є велика літера (y/n): ";
    cin >> has_capital_l;
    if (!(has_capital_l == 'y' || has_capital_l == 'n')){
        cout << "Помилка: дозволено тільки y або n." << endl;
        return 1;
    }

    char has_symbol;
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> has_symbol;
    if (!(has_symbol == 'y' || has_symbol == 'n')){
        cout << "Помилка: дозволено тільки y або n." << endl;
        return 1;
    }



    int type_symb = 0;
    if (has_num == 'y'){
        type_symb ++;
    }
    if (has_capital_l == 'y'){
        type_symb ++;
       }
    if (has_symbol == 'y'){
        type_symb ++;
    }


    cout << endl;

    cout << "Мінімальні вимоги: ";
    if (p_length >= 8 && type_symb >= 2){
        cout << "ПРОЙДЕНО!" << endl;
    }
    else {
        cout << "НЕ ПРОЙДЕНО!" << endl;
    }


    int level;
    cout << "Рівень надійності: ";
    if (p_length < 6) {
        level = 1;
        cout << level << " - Дуже слабкий" << endl;
    }

    else if ( p_length < 8 || type_symb == 0){ // використовуємо для перевірки альтернативних умов
        level = 2;
        cout << level << " - Слабкий" << endl;
    }
     
    else if ( type_symb == 1){
        level = 3;
        cout << level << " - Середній" << endl;
    }

    else if ( p_length >= 12 && type_symb == 3){
        level = 5;
        cout << level << " - Дуже надійний" << endl;
    }

    else {
        level = 4;
        cout << level << " - Надійний" << endl;
    }


    cout << "Рекомендація: ";
    switch (level) // перевіряє левел і по його значенню вибирає case
    {
    case 1:
        cout << "Пароль надто короткий. Мінімум 8 символів." << endl;        
        break; // закінчує "перевірку" 
    
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
        cout << "Відмінно! Змінювати нічого не потрібно." << endl;        
        break;
    default:
        break;
    }

    if (has_num == 'n' && has_symbol == 'n' ){
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
    cout << endl;
    cout << endl;

    return 0;
}