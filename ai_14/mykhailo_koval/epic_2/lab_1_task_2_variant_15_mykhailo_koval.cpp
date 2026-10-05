#include <iostream>

using namespace std;

int main(){
    int m, n;
    cout << "Введіть значення m та n: ";
    cin >> m >> n;

    int result1 = n++ - m;
    cout << "1) n++ - m" << '\n';
    int n_updated = n;
    int m_updated = m;
    cout << "Результат: " << result1 << '\n';
    cout << "n = " << n_updated << " " << "m = " << m_updated << '\n';

    bool result2 = m-- > n;
    cout << "2) m-- > n" << '\n';
    int n_updated2 = n;
    int m_updated2 = m;
    cout << "Результат: " << result2 << '\n';
    cout << "n = " << n_updated2 << " " << "m = " << m_updated2 << '\n';

    bool result3 = n-- > m;
    cout << "3) n-- > m" << '\n';
    int n_updated3 = n;
    int m_updated3 = m;
    cout << "Результат: " << result3 << '\n';
    cout << "n = " << n_updated3 << " " << "m = " << m_updated3 << '\n';

    return 0;
}