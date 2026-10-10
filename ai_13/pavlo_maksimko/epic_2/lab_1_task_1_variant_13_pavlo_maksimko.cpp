/*Lab Task 1 - Порівняння типів даних float і double
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    float a_float, b_float;
    double a_double, b_double;

    cout << "Введіть значення a та b: ";
    cin >> a_double >> b_double;

    //Прирівнюємо значення типу float до типу double, адже double має більшу точність знаків після коми
    a_float = a_double;
    b_float = b_double;

    //Створюємо проміжні змінні в обчисленні для кращого збереження точності
    float c_float, d_float, e_float;

    c_float= (a_float - b_float) * (a_float - b_float);

    d_float = a_float * a_float - 2 * a_float * b_float;

    e_float = b_float * b_float;

    float res_float;

    //Рахуємо результат за допомогою проміжних змінних
    //Точність все одно буде малою через те, що тип даних float не зберігає в собі так багато знаків після коми, як double
    res_float = (c_float - d_float) / e_float;

    //За тим же принципом, що в обчисленні в типі даних float, у double створюємо проміжні змінні
    double c_double, d_double, e_double;
    
    c_double = (a_double - b_double) * (a_double - b_double);

    d_double = a_double * a_double - 2 * a_double * b_double;

    e_double = b_double * b_double;

    double res_double;

    //Рахуємо результат за допомогою проміжних змінних
    //Точність буде більшою, ніж у типі даних float, завдяки збереженню більшої кількості знаків після коми
    res_double = (c_double - d_double) / e_double;

    //Виводимо обидва результати пліч-о-пліч та бачимо велику різницю у відповіді
    //Похибка утворюється через точність збереження знаків після коми
    cout << "У типі даних float: " << res_float << endl;
    cout << "У типі даних double: " << res_double << endl;

    return 0;
}