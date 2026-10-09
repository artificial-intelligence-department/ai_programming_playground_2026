/*
    Задача: Лабораторна робота №1, завдання №2
    Варіант: 24
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>

using namespace std;

int main()
{
    int norig,morig,res1=0,n,m; // оголошення змінних
    bool res2=false,res3=false; // оголошення змінних типу bool
    cout<<"Введіть значення n: "; // запит на введення значення
    cin>>norig; 
    cout<<"Введіть значення m: "; // запит на введення значення
    cin>>morig;
    n=norig; // присвоєння значення n
    m=morig; // присвоєння значення m
    res1=n++ * m;
    cout<<"Результат обчислення виразу n++ * m: "<<res1<<endl; // виведення результату
    n=norig; 
    m=morig; 
    if(n++<m) res2=true;
    cout<<"Результат обчислення виразу n++<m: "; // виведення результату
    if(res2==true) cout<<"True"<<endl;
      else cout<<"False"<<endl;
    n=norig; 
    m=morig;
    if(m-->m)res3=true;
    cout<<"Результат обчислення виразу m-->m: "; // виведення результату
    if(res3==true) cout<<"True"<<endl;
      else cout<<"False"<<endl;

}