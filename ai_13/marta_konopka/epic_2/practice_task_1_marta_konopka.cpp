/*
Аналізатор надійності пароля
Конопка Марта СШІ-13
*/

#include<iostream>
using namespace std;

int main() {
    int length = 0;
    char numbers = ' ';
    char capital = ' ';
    char special_characters = ' ';

    cout << "Введіть довжину пароля:";
    cin >> length;

      // межа з інструкції безпеки: пароль в межах від 1 до 64 символів, інша довжина є некоректною для програми
        if(length < 1 || length > 64){
        cout << "Довжина пароля має бути від 1 до 64 символів.";
        return 1;
     }

     cout << "Чи є у паролі цифри (y/n):";
     cin >> numbers;

     // перевірка коректності відповідей, щоб запобігти некоректним обчисленням рівня надійності далі
     if (numbers != 'n' && numbers != 'y'){
        cout << " Введено неправильне значення. Введіть y або n";
        return 1;
     }

     cout << "Чи є у паролі великі літери (y/n:)";
     cin >> capital;

     if(capital != 'y' && capital != 'n'){
        cout << "Введено неправильне значення. Введіть y або n";
        return 1;
     }

     cout << "Чи є у паролі спеціальні символи (y/n):";
     cin >> special_characters;

     if(special_characters != 'y' && special_characters != 'n'){
        cout << "Введено неправильне значення. Введіть y або n";
        return 1;
     }

     // межа з інструкції безпеки: від 8 символів та принаймні 2 типи знаків є необхідним мінімумом для пройдення вимог
     if(length >= 8 && (numbers == 'y' && capital == 'y' || numbers == 'y' && special_characters == 'y' || capital == 'y' && special_characters == 'y')){
        cout  << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
     }
        else{
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
     }

     int level = 0;

     // послідовна класифікація складності: від найкоротших комбінацій до найбільш надійних варіантів із повним набором символів
     if(length < 6){
      level = 1;
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
     }
     else if(length < 8 || numbers == 'n' && capital == 'n' && special_characters == 'n'){
        level = 2;
        cout << "Рівень надійності: 2 - Слабкий" << endl;
     }
     else if(numbers == 'y' && capital == 'n' && special_characters == 'n'){
      level = 3;
      cout << "Рівень надійності: 3 - Середній" << endl;
     }
     else if (numbers == 'n' && capital == 'y' && special_characters == 'n'){
      level = 3;
      cout << "Рівень надійності: 3 - Середній" << endl;
     } 
     else if(numbers == 'n' && capital == 'n' && special_characters == 'y'){
      level = 3;
      cout << "Рівень надійності: 3 - Середній" << endl;
     }
     else if(length >= 12 && numbers == 'y' && capital == 'y' && special_characters == 'y'){
      level = 5;
      cout << "Рівень надійності: 5 - Дуже надійний" << endl;
     }
     else{
      level = 4;
      cout << "Рівень надійності: 4 - Надійний" << endl;
     }
     
     // видача відповідної поради залежно від обчисленого рівня складності
     switch(level){
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
      default:
      cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно" << endl;
      break;
     }
      // попередження для текстових паролів без цифр і інших символів
     if( numbers == 'n' && special_characters == 'n'){
      cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
     }

    return 0;
} 