#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    //PART 1

    //float part
    float a_f = 1000;
    float b_f = 0.0001;
    float one_f = pow((a_f + b_f), 2);
    float two_f = pow(a_f , 2) + 2 * a_f * b_f;
    float three_f = one_f - two_f;
    float four_f = pow(b_f, 2);
    float res_f = three_f / four_f;
    
    cout << fixed << setprecision(8) << "float res: " << res_f << endl;

    //double part

    double a_d = 1000;
    double b_d = 0.0001;
    double one_d = pow((a_d + b_d), 2);
    double two_d = pow(a_d, 2) + 2 * a_d * b_d;
    double three_d = one_d - two_d;
    double four_d = pow(b_d, 2);
    double res_d = three_d / four_d;
    
    cout << fixed << setprecision(8) << "double res: " << res_d << endl << endl;

    //PART 2

    int m = 0;
    int n = 0;
    cout<<"enter m&n:"<<endl;
    cin>>m>>n;

    int m_tmp = m;
    int n_tmp = n;
    int step_1 = n_tmp++ + m_tmp; //n+m; n = n+1
    cout << "m: " << m_tmp << ", n: " << n_tmp << ", res: " << step_1 << endl;

    m_tmp = m;
    n_tmp = n;
    bool step_2 = m_tmp-- > n_tmp; // same to step 1
    cout << "m: " << m_tmp << ", n: " << n_tmp << ", res: " << boolalpha << step_2 << endl;

    m_tmp = m;
    n_tmp = n;
    bool step_3 = n_tmp-- > m_tmp; // same to step 1
    cout << "m: " << m_tmp << ", n: " << n_tmp << ", res: " << boolalpha << step_3 << endl << endl;

    return 0;
}