
#include <iostream>
#include <cmath>
using namespace std;
int main () {
    int n, m;
    cout << "Введіть значення n і m: ";
    cin >> n >> m;
// 1) n++ * m: береться старе n, потім n збільшується
    int n1=n, m1=m;
    int r1=n1++ * m1;
    cout << " n++ * m: результат: " << r1 << " , n = " << n1 << " , m = " << m1 << endl;
// 2) n++ < m: порівнюється старе n з m, потім n збільшується
    int n2=n, m2=m;
    bool r2=n2++ < m2;
    cout << " n++ < m: результат: " << r2 << " , n = " << n2 << " , m = " << m2 << endl;
// 3) m-- > m: зліва старе m, справа вже зменшене m
    int n3=n, m3=m;
    bool r3=m3-- > m3;
    cout << " m-- > m: результат: " << r3 << " , n = " << n3 << " , m = " << m3 << endl;

    return 0;
}
