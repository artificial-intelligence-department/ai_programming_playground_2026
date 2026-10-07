#include <iostream>
#include <iomanip>
using namespace std;

int main() {
   
    float a_f = 1000.0;
    float b_f = 0.0001;

  
    float chysl_f = (a_f + b_f) * (a_f + b_f) - (a_f * a_f + 2 * a_f * b_f);
    float  znam_f = b_f * b_f;
    float result_f = chysl_f / znam_f;

  
    cout << setprecision(8);
    cout << "Результат float: " << result_f << endl;

    double a_d = 1000.0;
    double b_d = 0.0001;

    // Окремо обчислюємо чисельник і знаменник.
    double chysl_d = (a_d + b_d) * (a_d + b_d) - (a_d * a_d + 2 * a_d * b_d);
    double  znam_d = b_d * b_d;
    double result_d = chysl_d / znam_d;

   
    cout << setprecision(15);
    cout << "Результат double: " << result_d<< endl;

    return 0;
}
