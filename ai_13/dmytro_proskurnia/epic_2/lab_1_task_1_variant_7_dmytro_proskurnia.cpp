#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    const float a_f = 1000.0f, b_f = 0.0001f;

    //використовується powf та запис n.0f для того щоб не було приведення до типу double
    const float f_numerator = powf((a_f - b_f), 3.0f) - (powf(a_f, 3.0f));
    const float f_denuminator = powf(b_f, 3.0f) - 3.0f * a_f * powf(b_f, 2.0f) - 3.0f * powf(a_f, 2.0f) * b_f;
    const float f_result = f_numerator / f_denuminator;

    const double a_d = 1000.0, b_d = 0.0001;

    const double d_numerator = pow((a_d - b_d), 3.0) - (pow(a_d, 3.0));
    const double d_denuminator = pow(b_d, 3.0) - 3.0 * a_d * pow(b_d, 2.0) - 3.0 * pow(a_d, 2.0) * b_d;
    const double d_result = d_numerator / d_denuminator;

    std::cout << std::fixed << std::setprecision(10) << "Calclulations in float: " << f_result << std::endl;
    std::cout << std::fixed << std::setprecision(10) << "Calclulations in double: " << d_result << std::endl;


    return 0;
}