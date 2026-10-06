/*
Task: self_practice_algotester_task_1 (Автомобіль Санта Клауса)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/
#include <iostream>
#include<iomanip>

using namespace std;
int main (){
    const long double pi = 3.141592653589793;
    double x , r = 0;
    int k = 0;
    cin >> x >> k >> r;
    long double res = x*k*pi*2.0*r;
    cout << fixed << setprecision(8) << res << endl;

    return 0;
}
