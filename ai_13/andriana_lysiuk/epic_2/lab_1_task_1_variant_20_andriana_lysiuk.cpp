/* Lab 1 task 1
Лисюк Андріана
ШІ-13
Варіант 20 */

#include <iostream>
#include <cmath>

using namespace std;
float a1 = 100;
float b1 = 0.001;
float numerator1 = 0.0;
float denominator1 = 0.0;
float result1 = 0.0;

double a2 = 100;
double b2 = 0.001;
double numerator2 = 0.0;
double denominator2 = 0.0;
double result2 = 0.0;

int main(){
   numerator1 = pow(a1+b1, 4) - (pow(a1, 4) + 4 * pow(a1, 3) * b1);
   denominator1 = 6 * pow(a1, 2) * pow(b1, 2) + 4 * a1 * pow(b1, 3) + pow(b1, 4);
   result1 = numerator1 / denominator1;
   // float: використовує 4 байти, менша точність (~7 значущих цифр) та може накопичувати похибку
   cout << "Result (if every variable is float): " << result1 << endl;

   numerator2 = pow(a2+b2, 4) - (pow(a2, 4) + 4 * pow(a2, 3) * b2);
   denominator2 = 6 * pow(a2, 2) * pow(b2, 2) + 4 * a2 * pow(b2, 3) + pow(b2, 4);
   result2 = numerator2 / denominator2;
   // double: використовує 8 байтів, більша точність (~15-16 значущих цифр)
   cout << "Result (if every variable is double): " << result2 << endl;
   
    return 0;
}