#include<iostream>
using namespace std;

int main() {
    int n_orig;
    int m_orig;

    cout << "Введіть n:" << endl;
    cin >> n_orig;
    cout << "Введіть m:" << endl;
    cin >> m_orig;
    
    int n = n_orig;
    int m = m_orig;

    cout << "Initial values: n = " << n << ", m = " << m << "\n\n";

    int res1 = n - --m;
    cout << "1) n - --m = " << res1 << " (n = " << n << ", m = " << m << ")\n";

    n = n_orig;
    m = m_orig;

    bool res2 = m-- < n;
    cout << "2) m-- < n = " << (res2 ? "true" : "false") << " (n = " << n << ", m = " << m << ")\n";

    n = n_orig;
    m = m_orig;

    bool res3 = n++ > m;
    cout << "3) n++ > m = " << (res3 ? "true" : "false") << " (n = " << n << ", m = " << m << ")\n";

    return 0;
}