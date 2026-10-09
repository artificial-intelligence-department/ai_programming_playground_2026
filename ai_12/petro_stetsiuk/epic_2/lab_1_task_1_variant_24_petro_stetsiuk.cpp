/*
    Задача: Лабораторна робота №1, завдання №1
    Варіант: 24
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    // Блок обчислень для типу float
    float a=1000,b=0.0001; // значення a та b за умовою

    // Обчислення чисельника
    float chessum=a+b;
    float chesstep= pow(chessum,3); // (a+b)^3
    float stepa=pow(a,3);
    float diffchesel=chesstep-stepa; // (a+b)^3 - a^3
    
    // обчислення знаменника
    float znamd1= 3*a*b*b;
    float stepb=pow(b,3);
    float znamd2= 3*a*a*b;
    float znamsum=znamd1+stepb+znamd2; // 3ab^2 + b^3 + 3a^2b

    // обчислення кінцевого результату
    float finalfloat=diffchesel/znamsum; // ((a+b)^3 - a^3)/(3ab^2 + b^3 + 3a^2b)

    // Блок обчислень для типу float
    double ad=1000,bd=0.0001; // значення a та b за умовою

    // Обчислення чисельника
    double chessumd=ad+bd;
    double chesstepd= pow(chessumd,3); // (a+b)^3
    double stepad=pow(ad,3);
    double diffcheseld=chesstepd-stepad; // (a+b)^3 - a^3

    // обчислення знаменника
    double dznamd1= 3*ad*bd*bd;
    double stepbd=pow(bd,3);
    double dznamd2= 3*ad*ad*bd;
    double znamsumd=dznamd1+stepbd+dznamd2; // 3ab^2 + b^3 + 3a^2b

    // обчислення кінцевого результату
    double finaldouble = diffcheseld/znamsumd; // ((a+b)^3 - a^3)/(3ab^2 + b^3 + 3a^2b)

    // Виведення результатів
    cout<<"Результат обчислення для даних типу float: "<<finalfloat<<endl;
    cout<<"Результат обчислення для даних типу double: "<<finaldouble<<endl;
    return 0;
}