#include <iostream>

using namespace std;

int main() {
    // Початкові дані для float
    float a_flt = 1000.0f;
    float b_flt = 0.0001f;

    // Обчислення для чисельника з float
    float diff_flt = a_flt - b_flt; 
    float term1_flt = diff_flt * diff_flt * diff_flt * diff_flt; // (a - b)^4
    float term2_flt = a_flt * a_flt * a_flt * a_flt;             // a^4
    float term3_flt = 4.0f * a_flt * a_flt * a_flt * b_flt;       // 4 * a^3 * b
    float term4_flt = 6.0f * a_flt * a_flt * b_flt * b_flt;       // 6 * a^2 * b^2

    // Обчислення для знаменника з float
    float term5_flt = b_flt * b_flt * b_flt * b_flt;             // b^4
    float term6_flt = 4.0f * a_flt * b_flt * b_flt * b_flt;       // 4 * a * b^3

    float numerator_flt = term1_flt - (term2_flt - term3_flt + term4_flt); // Чисельник
    float denominator_flt = term5_flt - term6_flt;               // Знаменник

    float res_flt = numerator_flt / denominator_flt;            // Підсумковий результат float


    // Початкові дані для double
    double a_dbl = 1000.0;
    double b_dbl = 0.0001;

    // Обчислення для чисельника з double
    double diff_dbl = a_dbl - b_dbl; 
    double term1_dbl = diff_dbl * diff_dbl * diff_dbl * diff_dbl; // (a - b)^4
    double term2_dbl = a_dbl * a_dbl * a_dbl * a_dbl;             // a^4
    double term3_dbl = 4.0 * a_dbl * a_dbl * a_dbl * b_dbl;       // 4 * a^3 * b
    double term4_dbl = 6.0 * a_dbl * a_dbl * b_dbl * b_dbl;       // 6 * a^2 * b^2

    // Обчислення для знаменника з double
    double term5_dbl = b_dbl * b_dbl * b_dbl * b_dbl;             // b^4
    double term6_dbl = 4.0 * a_dbl * b_dbl * b_dbl * b_dbl;       // 4 * a * b^3

    double numerator_dbl = term5_dbl - term6_dbl;                 // Чисельник
    double denominator_dbl = term5_dbl - term6_dbl;               // Знаменник

    double res_dbl = numerator_dbl / denominator_dbl;            // Підсумковий результат double


    // Вивід результатів
    cout << "Float result: " << res_flt << endl;
    cout << "Double result: " << res_dbl << endl;

    return 0;
}