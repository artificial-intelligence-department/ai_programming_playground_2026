/* 
Епік 2. lab_1_task_1_variant_11
Авторка: Софія Ліс
Група: ші-11
*/
#include <iostream>
#include <math.h>

using namespace std;

int main() {
    float a = 100;
    float b = 0.001f;

    float amb = a - b;
    float ambp4 = pow(amb, 4);  // перша дужка чисельника
    float ap4 = pow(a, 4);
    float ap3 = pow(a, 3);
    float fmap3mb =  4 * ap3 * b; 
    float sb = ap4 - fmap3mb;  // друга дужка чисельника
    float num = ambp4 - sb;  //чисельник увесь
    float ap2 = pow(a, 2);
    float bp2 = pow(b, 2);
    float fm = 6 * ap2 * bp2;  // зменшуване знаменника
    float bp3 = pow(b, 3);
    float fs = 4 * a * bp3;  // від'ємник знаменника
    float bp4 = pow(b, 4);
    float den = fm - fs + bp4;  // знаменник увесь
    float result = num / den;

    cout << "Float result: " << result << endl;

    double a_d = 100;
    double b_d = 0.001;

    double amb_d = a_d - b_d;
    double ambp4_d = pow(amb_d, 4);  // перша дужка чисельника
    double ap4_d = pow(a_d, 4);
    double ap3_d = pow(a_d, 3);
    double fmap3mb_d =  4 * ap3_d * b_d; 
    double sb_d = ap4_d - fmap3mb_d;  // друга дужка чисельника
    double num_d = ambp4_d - sb_d;  //чисельник увесь
    double ap2_d = pow(a_d, 2);
    double bp2_d = pow(b_d, 2);
    double fm_d = 6 * ap2_d * bp2_d;  // зменшуване знаменника
    double bp3_d = pow(b_d, 3);
    double fs_d = 4 * a_d * bp3_d;  // від'ємник знаменника
    double bp4_d = pow(b_d, 4);
    double den_d = fm_d - fs_d + bp4_d;  // знаменник увесь
    double result_d = num_d / den_d;

    cout << "Double result: " << result_d << endl;

    return 0;
}