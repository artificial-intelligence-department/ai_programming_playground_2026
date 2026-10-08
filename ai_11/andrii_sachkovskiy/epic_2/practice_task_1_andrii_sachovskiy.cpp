/*
    Задача: epic 2 practice_task
    Автор: Сачковський Андрій
    Група: ШІ-11
*/
#include <iostream>
using namespace std;
int main(){


int dovzhina;
char chislo;    
char bukva;   
char simvol;    
int riven;      
int t=0;      

// Ввід довжини та перевірка межі від 1 до 64
cout<<"Введіть довжину пароля від 1-64: ";
cin>>dovzhina;
if (dovzhina<1 || dovzhina>64){  
cout<<"Помилка: довжина мусить бути від 1 до 64."<<endl;
return 0;   
}

// Цифри перевірка
cout<<"Чи є цифри (y/n): ";
cin>>chislo;
switch (chislo)
{
case 'y':
t=t+1;      // +1 тип символів
break;
case 'n':
break;
default:  
cout<<"Помилка: введіть y або n."<<endl;
return 0;
}

// Великі літери
cout<<"Чи є великі літери (y/n): ";
cin>>bukva;
switch (bukva){
case 'y':
t=t+1;
break;
case 'n':
break;
default:
cout<<"Помилка: введіть y або n."<<endl;
return 0;
}

// Спеціальні символи
cout<<"Чи є спеціальні символи (y/n): ";
cin>>simvol;
switch (simvol){
case 'y':
t=t+1;
break;
case 'n':
break;
default:
cout<<"Помилка: введіть y або n."<<endl;
return 0;
}

// Мінімальні вимоги 
if(dovzhina >= 8 && t >= 2)   
{
cout<<"Мінімальні вимоги: ПРОЙДЕНО"<<endl;
}
else
{
cout<<"Мінімальні вимоги: НЕ ПРОЙДЕНО"<<endl;
}

// Рівень надійності 
if (dovzhina<6){
riven=1;
cout<<"Рівень надійності: 1 - Дуже слабкий"<<endl;
}
else if(dovzhina<8 || t==0)  
{
riven=2;
cout<<"Рівень надійності: 2 - Слабкий"<<endl;
}
else if (t==1){
riven=3;
cout<<"Рівень надійності: 3 - Середній"<<endl;
}
else if (dovzhina>=12 && t==3){   
riven=5;
cout<<"Рівень надійності: 5 - Дуже надійний"<<endl;
}
else    
{
riven=4;
cout<<"Рівень надійності: 4 - Надійний"<<endl;
}

// Рекомендація за рівнем
switch (riven){
case 1:
cout<<"Рекомендація: Пароль надто короткий. Мінімум 8 символів."<<endl;
break;
case 2:
cout<<"Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<<endl;
break;
case 3:
cout<<"Рекомендація: Додайте ще один тип символів або збільште довжину до 12."<<endl;
break;
case 4:
cout<<"Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів."<<endl;
break;
case 5:
cout<<"Рекомендація: Відмінно. Змінювати нічого не потрібно."<<endl;
break;

}

// Попередження немає ні цифр, ні спецсимволів
if (!(chislo=='y') && !(simvol=='y')){
cout<<"Попередження: пароль тільки з літер підбирається швидше."<<endl;
}

return 0;
}