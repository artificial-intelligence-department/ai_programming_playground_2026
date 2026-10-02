/* Аналізатор надійності пароля
Автор: Давидович Святослав
Група: ШІ-11
 */
#include <iostream>

using namespace std;

int main() {
    // оголошення змінних довжини та наявності типу символів
    int length;
    char type1, type2, type3; 

    // константи для майбутніх перевірок
    const int MIN_length = 1, MAX_length = 64;
    const int MINREQ_length = 8, MINREQ_Ctype = 2;
    const int LIMIT1_length = 6; 
    const int LIMIT2_length = 8, LIMIT2_Ctype = 0;
    const int LIMIT3_Ctype = 1;
    const int LIMIT5_length = 12, LIMIT5_Ctype = 3;

    // ввід та валідація даних
    // cin >> length не запише значення при неправильному типі і поверне false, надалі аналогічна логіка
    cout << "Довжина пароля: ";
    if (!(cin >> length)){
        cout << "помилка вводу: значення не є цілим числом" << endl;
        return 1;
    }
    if (length < MIN_length || length > MAX_length){
        cout << "помилка вводу: значення виходить за допустимі межі(від 1 до 64)" << endl;
        return 1;
    }

    cout << "Чи є цифри(y,n): ";
    if (!(cin >> type1) || (type1 != 'y' && type1 != 'n')){
        cout << "помилка вводу: введене значення не є символом n або y" << endl;
        return 1;
    }

    cout << "Чи є великі літери(y,n): ";
    if (!(cin >> type2) || (type2 != 'y' && type2 != 'n')){
        cout << "помилка вводу: введене значення не є символом n або y" << endl;
        return 1;
    }
    
    cout << "Чи є спеціальні символи(y,n): ";
    if (!(cin >> type3) || (type3 != 'y' && type3 != 'n')){
        cout << "помилка вводу: введене значення не є символом n або y";
        return 1;
    }

    // уведення змінної-кількості ствердних відповідей
    // для обчислення використовуємо неявне перетворення bool до int
    int Ctype = int(type1=='y') + int(type2=='y') + int(type3=='y');

    //перевірка на мінімальні вимоги
    if (length>=MINREQ_length && Ctype>=MINREQ_Ctype){
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }
    
    // визначення рівня надійності
    int level;

    cout << "Рівень надійності: ";
    if (length<LIMIT1_length){
        level = 1;
        cout << "1 - Дуже слабкий" << endl;
    } else if (length<LIMIT2_length || Ctype == LIMIT2_Ctype){
        level = 2;
        cout << "2 - Cлабкий" << endl;
    } else if (Ctype == LIMIT3_Ctype){
        level = 3;
        cout << "3 - Середній" << endl;
    } else if (length >= LIMIT5_length && Ctype == LIMIT5_Ctype){
        level = 5;
        cout << "5 - Дуже надійний" << endl;
    } else{
        level = 4;
        cout << "4 - Надійний" << endl;
    }

    // рекомендації відповідно до рівня
    cout << "Рекомендація: ";
    switch (level)
    {
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
        cout << "Невідоме значення" << endl;
    }
    

    // попередження виводимо тільки тоді, коли пароль складається лише з літер
    if (type1=='n' && type3=='n'){
        cout << "Попередження: Пароль тільки з літер підбирається швидше." << endl;
    }
    
    return 0;
}