/*Lab 1 Task 1 Variant 10
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <cmath>
using namespace std;
/*Задаємо функції для обчислення значення виразу для float та double,
до яких ми звернемося у тілі коду*/
float result(float a, float b){
    float step_1, step_2, step_3, step_4, result;
    //рахуємо (a-b)^4
    step_1=pow(a-b,4);
    //рахуємо дужку (a^4 - 4a^3b + 6a^2b^2)
    step_2=pow(a,4)-4*pow(a,3)*b+6*pow(a,2)*pow(b,2);
    //рахуємо знаменник (b^4-4ab^3)
    step_3=pow(b,4)-4*a*pow(b,3);
    //рахуємо весь чисельник (a-b)^4-(a^4 - 4a^3b + 6a^2b^2)
    step_4=step_1-step_2;
    //рахуємо результат всього виразу
    result=step_4/step_3;
    return result;
}
double result(double a, double b){
    double step_1, step_2, step_3, step_4, result;
    //рахуємо (a-b)^4
    step_1=pow(a-b,4);
    //рахуємо дужку (a^4 - 4a^3b + 6a^2b^2)
    step_2=pow(a,4)-4*pow(a,3)*b+6*pow(a,2)*pow(b,2);
    //рахуємо знаменник (b^4-4ab^3)
    step_3=pow(b,4)-4*a*pow(b,3);
    //рахуємо весь чисельник (a-b)^4-(a^4 - 4a^3b + 6a^2b^2)
    step_4=step_1-step_2;
    //рахуємо результат всього виразу
    result=step_4/step_3;
    return result;
}
int main() {
    //за замовчуванням оголошуємо a, b як double
    double a, b;
    cout<<"Введіть a та b: ";
    cin>>a>>b;
    float res_float;
    res_float=result((float) a, (float) b);
    cout<<"Результат для float: "<<res_float<<endl;
    double res_double;
    res_double=result(a,b);
    cout<<"Результат для double: "<<res_double<<endl;
    return 0;
}