/*
Аналізатор складності паролю
Артюх Іван
ШІ-12
 */
#include <iostream>

using namespace std;


int main(){


    int len = 0;// Довжина паролю

    char nums;// Чи є цифри (y/n)

    char caps;// Чи є великі літери (y/n)

    char specials;// Чи є спеціальні символи (y/n)    

    bool nums_bool;// Булева змінна для цифр

    bool caps_bool;// Булева змінна для великих літер

    bool specials_bool;// Булева змінна для спеціальні символів


    //Читання довжини паролю, валідація

    cout<<"Довжина пароля: ";

    cin>>len;

    if(cin.fail() || len > 64 ||  len < 1){

         cout<< "Довжина пароля має бути числом від 1 до 64."<<endl;

         return 1;

    }


    //Читання змінних "чи є...?", валідація, створення булових змінних відповідно до введених

    cout<<"Чи є цифри (y/n): ";

    cin>>nums;

    if(nums != 'y' && nums != 'n'){

         cout<< "Відповіддю має бути лише y або n."<<endl;

         return 1;

    }

    (nums == 'y')? nums_bool = 1 : nums_bool = 0;


    cout<<"Чи є великі літери (y/n): ";

    cin>>caps;

    if(caps != 'y' && caps != 'n'){

         cout<< "Відповіддю має бути лише y або n."<<endl;

         return 1;

    }

    (caps == 'y')? caps_bool = 1 : caps_bool = 0;


    cout<<"Чи є спеціальні символи (y/n): ";

    cin>>specials;

    if(specials != 'y' && specials != 'n'){

        cout<< "Відповіддю має бути лише y або n."<<endl;

        return 1;

    }

    (specials == 'y')? specials_bool = 1 : specials_bool = 0;


    int types_count = nums_bool+caps_bool+specials_bool;


    // Перевірка на мінімальні вимоги

    cout<<"Мінімальні вимоги: ";

    if(len >= 8 && types_count>=2){

        cout<<"ПРОЙДЕНО"<<endl;

    }


    else{

        cout<<"НЕ ПРОЙДЕНО"<<endl;

    }


    //Визначення рівня надійності, його запис у змінну

    cout<<"Рівень надійності: ";

    short int level = 0;


    if(len < 6){

        cout<<"1 - Дуже слабкий"<<endl;

        level = 1;

    }


    else if(len < 8 || types_count == 0){

        cout<<"2 - Слабкий"<<endl;

        level = 2;

    }

    else if(types_count == 1){

        cout<<"3 - Середній"<<endl;

        level = 3;

    }


    else if(len >= 12 && types_count == 3){

        cout<<"5 - Дуже надійний"<<endl;

        level = 5;


    }


    else{

        cout<<"4 - Надійний"<<endl;

        level = 4;

    }


    //виведення рекомендації відповідно до рівня надійності

    cout<<"Рекомендація: ";

    switch(level){

        case 1: cout<<"Пароль надто короткий. Мінімум 8 символів."<<endl;

        break;

        case 2: cout<<"Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<<endl;

        break;

        case 3: cout<<"Додайте ще один тип символів або збільште довжину до 12."<<endl;

        break;

        case 4: cout<<"Хороший пароль. Для максимуму 12+ символів і всі три типи символів."<<endl;

        break;

        case 5: cout<<"Відмінно. Змінювати нічого не потрібно."<<endl;

        break;

        default: cout<<"Упс! Виникла проблема під час пошуку  поради щодо вашого пароля :("<<endl;

        return 1;

    }


    //виведення попередження для паролів тільки із букв

    if(!(nums_bool || specials_bool)){

        cout<< "Попередження: пароль тільки з літер підбирається швидше."<<endl;

    }

    return 0;

}