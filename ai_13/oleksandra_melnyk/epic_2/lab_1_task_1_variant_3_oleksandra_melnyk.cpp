// Lab 1, task 1, Мельник Олександра, варіант 3
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main()
{
    /*
    Умова:
    (((a+b)^3)-(a^3+3*a^2*b))/(3*a*b^2+b^3)
    при а=1000, b=0.0001
    Розв'язок:
    дія1=(a+b)^3
    дія2=a^3
    дія3=3*a^2*b
    дія4=3*a*b^2
    дія5=b^3
    дія6(чисельник)=дія1-(дія2+дія3)
    дія7(знаменник)=дія4+дія5
    дія8(результат)=дія6(чисельник)/дія7(знаменник)
    */
//обчислення через float
    float a=1000;
    float b=0.0001;
    float action1=pow((a+b),3);
    float action2=pow(a,3);
    float action3=3*pow(a,2)*b;
    float action4=3*a*pow(b,2);
    float action5=pow(b,3);
    float numerator=action1-(action2+action3);
    float denominator =action4+action5;
    float result=numerator/denominator;

//обчислення через double
    double a1=1000;
    double b1=0.0001;
    double action_1=pow((a1+b1),3);
    double action_2=pow(a1,3);
    double action_3=3*pow(a1,2)*b1;
    double action_4=3*a1*pow(b1,2);
    double action_5=pow(b1,3);
    double numerator_1=action_1-(action_2+action_3);
    double denominator_1 =action_4+action_5;
    double finalresult=numerator_1/denominator_1;

    cout<<"Вивід через тип даних float: "<<fixed<<setprecision(10)<<result<<endl;
    cout<<"Вивід через тип даних double: "<<fixed<<setprecision(10)<<finalresult<<endl;
    return 0;
}


