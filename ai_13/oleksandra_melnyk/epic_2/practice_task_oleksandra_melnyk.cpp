#include <iostream>
#include <string>
using namespace std;
int main()
{
    int passwordlength, typecount=0, securitylevel=0;
    char hasnumber, hasupper, hasspecial;
    cout<<"Довжина пароля: ";
    cin>>passwordlength;
    if (passwordlength>64 || passwordlength<1)
    {
        cout<<"Помилка. Пароль повинен бути від 1 до 64 символів.";
        return 1;
    }
    cout<<"Чи є цифри?";
    cin>>hasnumber;
    if (hasnumber!='y' && hasnumber!='n')
    {
        cout<<"Помилка.Відповідь має бути тільки y або n";
        return 1;
    }
    if (hasnumber=='y')
    {
        typecount++;
    }
    cout<<"Чи є великі літери?";
    cin>>hasupper;
    if (hasupper!='y' && hasupper!='n')
    {
        cout<<"Помилка.Відповідь має бути тільки y або n";
        return 1;
    }
    if (hasupper=='y')
    {
        typecount++;
    }
    cout<<"Чи є спеціальні символи?";
    cin>>hasspecial;
    if (hasspecial!='y' && hasspecial!='n')
    {
        cout<<"Помилка.Відповідь має бути тільки y або n";
        return 1;
    }
    if (hasspecial=='y')
    {
        typecount++;
    }
    if (passwordlength<6)
    {
        securitylevel=1;
    }
    else if (passwordlength<8 || typecount==0)
    {
        securitylevel=2;
    }
    else if (typecount==1)
    {
        securitylevel=3;
    }
    else if (passwordlength>=12 && typecount==3)
    {
        securitylevel=5;
    }
    else {
        securitylevel=4;
    }

    if (passwordlength>=8 && securitylevel>=2)
    {
        cout<<"Мінімальні вимоги: ПРОЙДЕНО"<<endl;
    }
    else
    {
        cout<<"Мінімальні вимоги: НЕ ПРОЙДЕНО"<<endl;
    }
    cout << "Рівень надійності: " << securitylevel << endl;
    switch (securitylevel)
    {
        case 1:
        cout<<"Пароль надто короткий. Мінімум 8 символів."<<endl;
        break;
        case 2:
        cout<<"Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи"<<endl;
        break;
        case 3:
        cout<<"Додайте ще один тип символів або збільште довжину до 12."<<endl;
        break;
        case 4:
        cout<<"Хороший пароль. Для максимуму 12+ символів і всі три типи символів"<<endl;
        break;
        case 5:
        cout<<"Відмінно. Змінювати нічого не потрібно"<<endl;
        break;
        default:
        cout<<"Помилка визначення рівня надійності";

    }
    if (hasnumber == 'n' && hasspecial == 'n') {
    cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
}
}