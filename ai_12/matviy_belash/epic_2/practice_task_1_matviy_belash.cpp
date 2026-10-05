/* 
Аналізатор надійності пароля
Белаш Матвій Валерійович
ШІ-12
*/
#include <iostream>
using namespace std;

int main() {

    int length_password = 0; //Оголошуємо та вводимо довжину пароля (+ перевіряємо на допустимі значення)
    cout << "Please enter the length of the password(min required is 8): ";
    cin >> length_password;
    if(length_password < 1 || length_password > 64){
        cout << "Valid values for length range from 1 to 64." << endl;
        return 0;
    }
    
    char simbols_password = ' '; //Вводимо наявність цифр у паролі (+ перевіряємо чи користувач ввів кореткне значення)
    cout << "Does your password contain numbers? (y/n): ";
    cin >> simbols_password;
    if (!(simbols_password == 'y' || simbols_password == 'n')) {
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        return 0;
    }
    
    char capital_letters_password = ' '; //Вводимо наявність великих літер у паролі (+ перевіряємо чи користувач ввів кореткне значення)
    cout << "Are there any capital letters? (y/n): ";
    cin >> capital_letters_password;
    if (!(capital_letters_password == 'y' || capital_letters_password == 'n')) {
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        return 0;
    }

    char special_simbols_password = ' '; //Вводимо наявність спеціальних символів у паролі (+ перевіряємо чи користувач ввів кореткне значення)
    cout << "Does your password contain special symbols? (y/n): ";
    cin >> special_simbols_password;
    if (!(special_simbols_password == 'y' || special_simbols_password == 'n')){
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        return 0;
    }

    int tipe_simbols = 0;  //визначаємо кількість типів символів у паролі
    if (simbols_password == 'y'){
        tipe_simbols += 1;
    } 
    if (capital_letters_password == 'y'){
        tipe_simbols += 1;
    }
    if (special_simbols_password == 'y'){
        tipe_simbols += 1;
    }
    
    int level = 0;

    if (length_password < 6){ //визначаємо рівень надійності пароля
        level = 1;
        cout << "Very weak" << endl;
    } else if(length_password < 8 || tipe_simbols == 0){
        level = 2;
        cout << "Weak" << endl;
    } else if (tipe_simbols == 1){
        level = 3;
        cout << "Average" << endl;
    } else if(length_password >= 12 && tipe_simbols == 3){
        level = 5;
        cout << "Very reliable" << endl;
    } else{
        level = 4;  
        cout << "Reliable" << endl;
    }

    /*
    Виводимо результати:
    1)Мінімальні вимоги: виконані/не виконані
    2)Рівень надійності: 1-5 та словесне пояснення
    3)Рекомендації щодо покращення пароля
    4) (У випадку, якщо пароль складається лише з літер) Попередження про те, що такі паролі зламуються швидше
    */

    cout << "---------------------------RESULTS-----------------------------------" << endl; 

    if (length_password < 8 || tipe_simbols < 2){       //1)
        cout << "Minimum Requirements: Not completed" << endl; 
    } else {
         cout << "Minimum Requirements: Completed" << endl;
    }

    if (level == 1){               //2)
        cout << "Reliability Level: 1 - Very weak" << endl;
    } else if (level == 2){
        cout << "Reliability Level: 2 - Weak" << endl;
    } else if (level == 3){
        cout << "Reliability Level: 3 - Average" << endl;
    } else if (level == 4){
        cout << "Reliability Level: 4 - Reliable" << endl;
    } else{
        cout << "Reliability Level: 5 - Very reliable" << endl;
    }
    
    switch (level) { //3)

        case 1:
        cout << "Recommendation: The password is too short. It must be at least 8 characters long." << endl;
        break;

        case 2: 
        cout << "Recommendation: Increase the length to 8+ characters and include numbers, uppercase letters, or special characters." << endl;
        break;

        case 3:
        cout << "Recommendation: Add another character type or increase the length to 12." << endl;
        break;

        case 4:
        cout << "Recommendation: A strong password. It should be at least 12 characters long and include all three types of characters." << endl;
        break;

        case 5:
        cout << "Recommendation: Great. Nothing needs to be changed." << endl;
        break;

        default:
        cout << "Unexpected level." << endl;
        break;
    }

    if (simbols_password == 'n' && special_simbols_password == 'n'){
        cout << "Warning: Passwords consisting only of letters are cracked more quickly." << endl;
    }

    return 0;

}