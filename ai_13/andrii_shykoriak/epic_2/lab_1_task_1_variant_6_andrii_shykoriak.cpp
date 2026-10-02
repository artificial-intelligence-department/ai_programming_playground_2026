#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main()
{
    // Lab 1 , task 1, Шикоряк Андрій,ШІ-13, Варіант 6
    /*
     Умова:
        (a-b)^3 - (a^3-3ab^2) / b^3 - 3a^2b
        при а = 1000, b = 0.0001
        
        Розв'язання:
        Дія 1 = a - b
        Дія 2 = Дія 1 ^ 3
        Дія 3 = a ^ 3
        Дія 4 = 3 * a * b^2
        Дія 5 = Дія 3 - Дія 4
        Дія 6 = Дія 2 - Дія 5
        Дія 7 = b ^ 3 
        Дія 8 = 3 * a ^ 2 * b
        Дія 9 = Дія 7 - Дія 8
        Дія 10 = Дія 6 / Дія 9
        
     */
    float a = 1000.0;
    float b = 0.0001;
    
    float action1 = a - b;
    float action2 = action1 * action1 * action1;
    float action3 = a * a *a ;
    float action4 = 3 * a * (b * b);
    float action5 = action3 - action4;
    float action6 = action2 - action5;
    float action7 = b * b * b;
    float action8 = 3 * (a * a) * b;
    float action9 = action7 - action8;
    float action10 = action6 / action9;
    
  
    
    
    // Обчисллення через Double 
    double a_d = 1000.0;
    double b_d = 0.0001;

    double action1_d = a_d - b_d;
    double action2_d = action1_d * action1_d * action1_d;
    double action3_d = a_d * a_d * a_d;
    double action4_d = 3 * a_d * (b_d * b_d);
    double action5_d = action3_d - action4_d;
    double action6_d = action2_d - action5_d;
    double action7_d = b_d*b_d*b_d;
    double action8_d = 3 * (a_d * a_d) * b_d;
    double action9_d = action7_d - action8_d;
    double action10_d = action6_d / action9_d;
    
    cout << "Результат обчислення через FLOAT:  " <<fixed<<setprecision(10)<< action10 << endl;
    cout << "Результат обчислення через DOUBLE: " <<fixed<<setprecision(10)<< action10_d << endl;

    return 0;
}