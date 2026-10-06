#include <iostream>
#include <iomanip>

using  namespace std;

int main() {

    float a_f = 1000;
    float b_f = 0.0001;
    //дії почергово з float змінними
    float first_f = (a_f - b_f) * (a_f - b_f) - (a_f * a_f - 2 * a_f * b_f);
    float second_f = b_f * b_f;
    float result_f = first_f / second_f;

    cout << fixed << setprecision(8) << "Float result: " << result_f << endl;

    double a_d = 1000;
    double b_d = 0.0001;
    //дії почергово з double змінними
    double first_d = (a_d - b_d) * (a_d - b_d) - (a_d * a_d - 2 * a_d * b_d); 
    double second_d = b_d * b_d;
    double result_d = first_d / second_d;

    cout << fixed << setprecision(8) << "Double result: " << result_d << endl;

    return 0;
}