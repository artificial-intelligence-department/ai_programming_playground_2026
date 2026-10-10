/*
Назва: Lab 1v1 | NULP_LABS_Programming_Basics_2026
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream>
using namespace std;

int main() {
    long long H, M;
    long long h1, m1;
    long long h2, m2;
    long long h3, m3;
    long long sum_h, sum_m;
    int e=0;
    cin >> H >> M;
    cin >> h1 >> m1;
    cin >> h2 >> m2;
    cin >> h3 >> m3;
    if (h1 == 0 || m1 == 0) {
    } else {
        e++; 
    }
    if (h2 == 0 || m2 == 0) {
    } else {
        e++;
    }
    if (h3 == 0 || m3 == 0) {
    } else {
        e++;
    }
    sum_h = h1 + h2 + h3;
    sum_m = m1 + m2 + m3;
    if (H> sum_h && M > sum_m) {

    } else { 
        e++;
    }

    if (e >= 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }


}