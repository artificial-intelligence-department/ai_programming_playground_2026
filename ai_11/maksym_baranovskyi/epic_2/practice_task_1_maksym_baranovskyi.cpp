#include <iostream>
using namespace std;

int main(){

    cout << "Введіть довжину пароля: ";
    int passwordLength;    
    if(!(cin >> passwordLength) || passwordLength < 1 || passwordLength > 64){
        cout << "Довжина паролю повинна бути цілим числом від 1 до 64.";
        return 1;
    }

    cout << "Пароль містить цифри (y/n)? ";
    char hasNumbers;
    if(!(cin >> hasNumbers) || (hasNumbers != 'y' && hasNumbers != 'n')){
        cout << "Значення повинне бути y або n." << endl;
        return 1;
    }

    cout << "Пароль містить великі літери (y/n)? ";
    char hasCapitalLetters;
    if(!(cin >> hasCapitalLetters) || (hasCapitalLetters != 'y' && hasCapitalLetters != 'n')){
        cout << "Значення повинне бути y або n" << endl;
        return 1;
    }

    cout << "Пароль містить спеціальні символи (y/n)? ";
    char hasSpecialSymbols;
    if(!(cin >> hasSpecialSymbols) || (hasSpecialSymbols != 'y' && hasSpecialSymbols != 'n')){
        cout << "Значення повинне бути y або n" << endl;
        return 1;
    }

    int symbolTypesCount = (hasNumbers == 'y') + (hasSpecialSymbols == 'y') + (hasCapitalLetters == 'y');

    if(passwordLength >= 8 && symbolTypesCount >= 2){
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else{
        cout << "Мінімальні вимоги: НЕПРОЙДЕНО" << endl;
    }

    int securityLevel;

    if(passwordLength < 6){
        securityLevel = 1;
        cout << "Рівень надійності: " << securityLevel << " - Дуже слабкий" << endl;
    }
    else if(passwordLength <= 8 || symbolTypesCount == 0){
        securityLevel = 2;
        cout << "Рівень надійності: " << securityLevel << " - Слабкий" << endl;
    }
    else if(symbolTypesCount == 1){
        securityLevel = 3;
        cout << "Рівень надійності: " << securityLevel << " - Середній" << endl;
    }
    else if(passwordLength >= 12 && symbolTypesCount == 3){
        securityLevel = 5;
        cout << "Рівень надійності: " << securityLevel << " - Дуже надійний" << endl;
    }
    else{
        securityLevel = 4;
        cout << "Рівень надійності: " << securityLevel << " - Надійний" << endl;
    }

    switch (securityLevel)
    {
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
    }

    if(hasNumbers != 'y'){
        cout << "Попередження: Пароль тільки з літер підбирається швидше." << endl;
    }


    return 0;
}