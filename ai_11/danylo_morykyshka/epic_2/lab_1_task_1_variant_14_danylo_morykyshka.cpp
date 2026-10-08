#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float a1 = 1000;
    float b1 = 0.0001;

    //Підношу значення змінних до квадрата та куба
    float a1Squared = pow(a1,2);
    float a1Cubed = pow(a1,3);
    float b1Squared = pow(b1,2);
    float b1Cubed = pow(b1,3);

    //Розбиваю вираз на дії та обчислюю значення виразу

    float step11 = pow(a1 + b1,3);
    
    float step12 = a1Cubed + 3*a1Squared*b1;
    float step13 = step11 - step12;
    float step14 = 3 * a1 * b1Squared + b1Cubed;
    float finalResFloat = step13/step14;

    //Виводжу фінальний результат обчислень для відповідного типу даних
    cout << "Float result: " << finalResFloat<< endl;

    double a2 = 1000;
    double b2 = 0.0001;

    double a2Squared = pow(a2,2);
    double a2Cubed = pow(a2,3);
    double b2Squared = pow(b2,2);
    double b2Cubed = pow(b2,3);

    double step21 = pow(a2 + b2,3);
    
    double step22 = a2Cubed + 3*a2Squared*b2;
    double step23 = step21 - step22;
    double step24 = 3 * a2 * b2Squared + b2Cubed;
    double finalResDouble = step23/step24;

    cout << "Double result: " << finalResDouble<< endl;

}