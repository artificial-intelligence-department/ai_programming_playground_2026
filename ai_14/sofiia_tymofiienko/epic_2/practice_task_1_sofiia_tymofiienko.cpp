/*Sofiia Tymofiienko SHi-14*/

//Підключаємо бібіліотеку

#include <iostream>
using namespace std;

//Вводимо змінні

int main(){
     int length;
    char hasDigits, hasUpper, hasSpecial;
cout<<" Введіть довжину пароля: ";
cin>> length;
if (length<1 || length >64){  //Перевіряємо умови вводу
    cout<<"Помилка, довжина паролю від 1 до 64 символів."<<endl; 
    return 0;
}
cout<<" Чи є цифри? (y/n) ";
cin>> hasDigits;
if(hasDigits !='y' && hasDigits!= 'n'){
    cout<< "Помилка, пароль повинен містити (y/n). "<<endl;
    return 0;
}
cout<<" Чи є великі літери? (y/n) ";
cin>> hasUpper;
if(hasUpper != 'y' && hasUpper != 'n'){
    cout<<" Помилка, пароль повинен містити великі літери (y/n). "<<endl;
    return 0;
}
cout<<"Чи є спеціальні символи? (y/n)";
cin>> hasSpecial;
if (hasSpecial != 'y'&& hasSpecial != 'n'){
    cout<<" Помилка, пароль повинен містити спеціальні символи (y/n)."<<endl;
    return 0;
}
// Підрахунок кількості типів символів (від 0 до 3)
int symbolnum=0;
if(hasDigits == 'y') symbolnum++;
if(hasUpper == 'y') symbolnum++;
if(hasSpecial == 'y') symbolnum++;

// Перевірка мінімальних вимог
bool passwordmin=false;
if (length>=8 && symbolnum>=2){
    passwordmin=true;
    cout<<" Перевірку мінімальних вимог пройдено. "<<endl;
}else{
    cout<<"Перевірку мінімальних вимог не пройдено. "<<endl;
}

//Визначаємо рівень надійності паролю
int level = 0;
    if (length < 6) {
        level = 1; 
    } 
    else if (length < 8 || symbolnum == 0) {
        level = 2; 
    } 
    else if (symbolnum == 1) {
        level = 3; 
    } 
    else if (length >= 12 && symbolnum == 3) {
        level = 5; 
    } 
    else {
        level = 4; 
    }

    cout << "Рівень надійності: " << level << " - ";
    if (level == 1) cout << "Дуже слабкий" << endl;
    else if (level == 2) cout << "Слабкий" << endl;
    else if (level == 3) cout << "Середній" << endl;
    else if (level == 4) cout << "Надійний" << endl;
    else if (level == 5) cout << "Дуже надійний" << endl;

    
    switch (level) { //Виводимо рекомендації щодо паролю користувача
        case 1:
            cout << "Рекомендація: «Пароль надто короткий. Мінімум 8 символів.»" << endl;
            break;
        case 2:
            cout << "Рекомендація: «Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.»" << endl;
            break;
        case 3:
            cout << "Рекомендація: «Додайте ще один тип символів або збільште довжину до 12.»" << endl;
            break;
        case 4:
            cout << "Рекомендація: «Хороший пароль. Для максимуму 12+ символів і всі три типи символів.»" << endl;
            break;
        case 5:
            cout << "Рекомендація: «Відмінно. Змінювати нічого не потрібно.»" << endl;
            break;
        default:
            cout << "Рекомендація відсутня." << endl;
            break;
    }

    if (!(hasDigits == 'y') && !(hasUpper == 'y') && !(hasSpecial == 'y')) {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;

}