#include <iostream>

using namespace std;
int main() {
    int n0, m0;
    cout << "Введіть значення n, m: " << endl;
    cin >> n0 >> m0;
    int n = n0;
    int m = m0;

    int res_1 = m-++n;
    n = n0; m = m0;
    bool res_2 = --n<++m;
    n = n0; m = m0;
    bool res_3 = --n<++m;
    n = n0; m = m0;
    cout << "m-++n = " << res_1 << endl;
    cout << "++m>--n = " << res_2 << endl;
    cout << "--n<++m = " << res_3 << endl;

}