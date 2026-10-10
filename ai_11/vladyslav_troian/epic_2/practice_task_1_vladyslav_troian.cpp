/* 
Задача: Автономність портативної зарядної станції
Автор: Троян Владислав
Група: AI-11
*/

#include <iostream>
using namespace std;

int main()
{
    int level = 0; //позначення надійності пароля 
    int sim_type = 0; //для визначення складності паролю

    int ps_length = 0;
    cout << "Довжина паролю: ";
    cin >> ps_length;
    if (ps_length <= 0 || ps_length > 64){
        cout << "Помилка. Довжина паролю повинна бути від 1 до 64" << endl;
        return 1;
    }

    char num;
    cout << "Чи є цифри? (y/n): ";
    cin >> num;
    if (num == 'y'){
        sim_type++;
    } else if (num == 'n'){
        ;
    } else {
        cout << "Помилка. Відповідь має бути y або n" << endl;
        return 1;
    }

    char upper_let;
    cout << "Чи є великі літери? (y/n): ";
    cin >> upper_let;
    if (upper_let == 'y'){
        sim_type++;
    } else if (upper_let == 'n'){
        ;
    } else {
        cout << "Помилка. Відповідь має бути y або n" << endl;
        return 1;
    }

    char spe_sim;
    cout << "Чи є спеціальні символи? (y/n): ";
    cin >> spe_sim;
    if (spe_sim == 'y'){
        sim_type++;
    } else if (spe_sim == 'n'){
        ;
    } else {
        cout << "Помилка. Відповідь має бути y або n" << endl;
    }

    cout << "---> Аналіз даних <---" << endl;

    //умова чи проходить пароль вимоги
    if (ps_length >= 8 && sim_type >= 2){
        cout << "Мінімальних вимог: ДОТРИМАНО" << endl;
    } else {
        cout << "Мінімальних вимог: НЕ ДОТРИМАНО" << endl;
    }

    //встановлюю умови для кожного 
    if (ps_length < 6){
        level = 1;
    } else if (ps_length < 8 || sim_type == 0){
        level = 2;
    } else if (ps_length < 8 || sim_type == 1){
        level = 3;
    } else if (ps_length >= 12 && sim_type == 3){
        level = 5;
    } else {
        level = 4;
    }

    //для виведення рекомендацій та опису рівня надійності
    switch(level){
        case 1:
        cout << "Рівень надійності: " << level << " - Дуже слабкий" << endl;
        cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
        break;
        case 2:
        cout << "Рівень надійності: " << level << " - Слабкий" << endl;
        cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
        break;
        case 3:
        cout << "Рівень надійності: " << level << " - Середній" << endl;
        cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
        break;
        case 5:
        cout << "Рівень надійності: " << level << " - Дуже надійний" << endl;
        cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
        break;
        default:
        cout << "Рівень надійності: " << level << " - Надійний" << endl;
        cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
        break;
    }

    if (num != 'y' && spe_sim != 'y'){
        cout << "Попередження: Пароль лише з літер можна відгадати ДУЖЕ ЛЕГКО!" << endl;
    }
    return 0;
}