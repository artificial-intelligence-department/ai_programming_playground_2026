/*
Task: Practice_task_Аналізатор надійності пароля
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>
#include <string>

using namespace std;
int main (){
    setlocale(LC_ALL, "uk_UA");

    const int MAX_LENGTH = 64; // Обмежуємо значення довжини паролю

  
    int password_len = 0;  //Довжина паролю введена користувачем
    char numbers = ' '; // Цифри так чи ні
    char capital = ' '; // Велика буква так чи ні
    char sp_symbols = ' '; // Спеціальні символи так чи ні

    cout << "Введіть довжину паролю (до 64 знаків): ";
    cin  >> password_len;

    cout << "Вкажіть чи є цифри у вашому паролі (yes - y / no - n): ";
    cin  >> numbers;

    cout << "Вкажіть чи є велика літера у вашому паролі (yes - y / no - n): ";
    cin  >> capital;

    cout << "Вкажіть чи є спеціальні символи у вашому паролі (yes - y / no - n): ";
    cin  >> sp_symbols;




    //Робимо перевірку введених користувачем значень
    bool bad_password_len = (password_len <=0 || password_len > MAX_LENGTH);
    bool bad_numbers = !(numbers == 'y' || numbers == 'n');
    bool bad_capital = !(capital == 'y' || capital == 'n');
    bool bad_sp_symbols = !(sp_symbols == 'y' || sp_symbols == 'n');

    if (bad_password_len || bad_numbers || bad_capital || bad_sp_symbols){
        cout << "НЕ коректний ввід. Спробуйте ввести дійсне значення!" << endl;
        return 1;
    }
        
    //Визначаємо рівень надійності паролю, перше правило, що спрацювало визначає відповідь
    int level = 0;
    string pass_identification;

    if (password_len >= 12 && numbers == 'y' && capital == 'y' && sp_symbols == 'y'){
        level = 5; 
        pass_identification = "Дуже надійний!";

    }else if (numbers == 'y' && capital == 'n' && sp_symbols == 'n' ||
              numbers == 'n' && capital == 'y' && sp_symbols == 'n' ||
              numbers == 'n' && capital == 'n' && sp_symbols == 'y')
    {
        level = 3;
        pass_identification = "Середній";

    }else if (password_len < 6)
    {
        level = 1; 
        pass_identification = "Дуже слабкий!";

    }else if (password_len < 8 || numbers == 'n' && capital == 'n' && sp_symbols == 'n')
    {
        level = 2; 
        pass_identification = "Слабкий";
    }else{
        level = 4; 
        pass_identification = "Надійний!";
    }



    // Перевірка на мінімальні вимоги
    bool min_requirements = (numbers == 'y' && capital == 'y'
                            || numbers == 'y' && sp_symbols == 'y'
                            || capital == 'y'  && sp_symbols == 'y'
                            || numbers == 'y' && capital == 'y' && sp_symbols == 'y');
    if (password_len >= 8 && min_requirements)
    {
        cout << "Мінімальні вимоги: Пройдено!" << endl;
    }else{
        cout << "Мінімальні вимоги: НЕ Пройдено!" << endl;
    }

    cout << "Рівень надійності: " << level << " — " << pass_identification << endl;

    // Даємо рекомендації користувачу щодо його паролю.
    switch (level)
    {
    case 1: cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів!" << endl; break;
    case 2: cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl; break;
    case 3: cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12" << endl; break;
    case 4: cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl; break;
    case 5: cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно" << endl; break;
    default:
        cout << " Рекомендація: У вас не достатньо хороший пароль, спробуйте подовжити його або додати більше типів символів" << endl;break;
    }


    if (numbers == 'n' && capital == 'n' && sp_symbols == 'n')
    {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
    
}