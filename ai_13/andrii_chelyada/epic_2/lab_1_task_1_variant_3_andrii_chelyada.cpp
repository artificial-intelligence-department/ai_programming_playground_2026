// lab 1, task 1, Челяда Андрій, ШІ-13, варіант 3
/* Умова:
    (a+b)^3 - (a^3 + 3a^2b)/ 3ab^2 +b^3
при а=1000
    b=0.0001
Розв'язання:
    Дія 1  = a + b
    Дія 2  = (a + b)^3         
    Дія 3  = a ^ 3
    Дія 4  = 3 * a ^ 2 * b
    Дія 5  = Дія 3 + Дія 4      // a^3 + 3a^2b
    Дія 6  = Дія 2 - Дія 5      // чисельник
    Дія 7  = 3 * a * b ^ 2
    Дія 8  = b ^ 3
    Дія 9  = Дія 7 + Дія 8      // знаменник
    Дія 10 = Дія 6 / Дія 9      // результат
*/  
#include <iostream>
#include <iomanip>
using namespace std;
int main() {

    // Обрахунки через double 
    double a = 1000;
    double b = 0.0001;
    double action1 = a + b;
    double action2 = action1 * action1 * action1; 
    double action3 = a * a * a;
    double action4 = 3 * a * a * b;
    double action5 = action3 + action4;
    double action6 = action2 - action5;
    double action7 = 3 * a * b * b;
    double action8 = b * b * b;
    double action9 = action7 + action8;
    double result = action6 / action9;

    //Обрахунки через float
    float a_f = 1000;
    float b_f = 0.0001;
    float action1_f = a_f + b_f;
    float action2_f = action1_f * action1_f * action1_f;
    float action3_f = a_f * a_f * a_f;
    float action4_f = 3 * a_f * a_f * b_f;
    float action5_f = action3_f + action4_f;
    float action6_f = action2_f - action5_f;
    float action7_f = 3 * a_f * b_f * b_f;
    float action8_f = b_f * b_f * b_f;
    float action9_f = action7_f + action8_f;
    float result_f = action6_f / action9_f; 

    cout << fixed << setprecision(10) << "Результат через double: " << result << endl;
    cout << fixed << setprecision(10) << "Результат через float: " << result_f << endl;
    return 0;
}