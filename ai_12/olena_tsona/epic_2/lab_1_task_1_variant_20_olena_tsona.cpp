/*
Lab 1 task 1, Цьона Олена, ШІ-12, Варіант 20
*/

/*
Умова:
((a + b)^4 - (a^4 + 4*a^3*b)) / (6*a^2*b^2 + 4*a*b^3 + b^4)
при a = 100, b = 0.001
*/

/*
Дії:
1. (a + b) = act1
2. act1^4 = act2
3. a^4 = act3
4. a^3 = act4
5. 4 * act4 * b = act5
6. act3 + act5 = act6
7. act2 - act6 = act7
8. a^2 = act8
9. b^2 = act9
10. 6 * act8 * act9 = act10
11. b^3 = act11
12. 4 * a * act11 = act12
13. b^4 = act13
14. act10 + act12 + act13 = act14
15. act7 / act14
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    cout << fixed << setprecision(10);

    float a_f = 100.0f;
    float b_f = 0.001f;

    float act1_f = a_f + b_f;
    float act2_f = pow(act1_f, 4);
    float act3_f = pow(a_f, 4);
    float act4_f = pow(a_f, 3);
    float act5_f = 4 * act4_f * b_f;
    float act6_f = act3_f + act5_f;
    float act7_f = act2_f - act6_f;
    float act8_f = pow(a_f, 2);
    float act9_f = pow(b_f, 2);
    float act10_f = 6 * act8_f * act9_f;
    float act11_f = pow(b_f, 3);
    float act12_f = 4 * a_f * act11_f;
    float act13_f = pow(b_f, 4);
    float act14_f = act10_f + act12_f + act13_f;
    float result_f = act7_f / act14_f;

    double a_d = 100.0;
    double b_d = 0.001;

    double act1_d = a_d + b_d;
    double act2_d = pow(act1_d, 4);
    double act3_d = pow(a_d, 4);
    double act4_d = pow(a_d, 3);
    double act5_d = 4 * act4_d * b_d;
    double act6_d = act3_d + act5_d;
    double act7_d = act2_d - act6_d;
    double act8_d = pow(a_d, 2);
    double act9_d = pow(b_d, 2);
    double act10_d = 6 * act8_d * act9_d;
    double act11_d = pow(b_d, 3);
    double act12_d = 4 * a_d * act11_d;
    double act13_d = pow(b_d, 4);
    double act14_d = act10_d + act12_d + act13_d;
    double result_d = act7_d / act14_d;

    cout << "Результат float: " << result_f << endl << endl;

    cout << "Результат double: " << result_d << endl;

    return 0;
}

