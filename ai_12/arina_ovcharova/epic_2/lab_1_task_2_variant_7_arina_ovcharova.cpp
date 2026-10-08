#include <iostream>

using namespace std;

// Lab 1, Task 2 (варіант 7): m+--n, m++<++n, n--<--m
// Кожен вираз обчислюється на копіях m та n із початковими значеннями.
int main() {
    int m, n;

    cout << "Lab 1 Task 2, variant 7\n";
    cout << "Введіть два цілі числа m та n:\n";
    cin >> m >> n;

    // 1) m + --n
    {
        int m1 = m;
        int n1 = n;
        int result = m1 + --n1;

        cout << "\n1) m + --n\n";
        cout << "Резултат = " << result << '\n';
        cout << "m = " << m1 << ", n = " << n1 << '\n';
    }

    // 2) m++ < ++n
    {
        int m2 = m;
        int n2 = n;
        bool result = m2++ < ++n2;

        cout << "\n2) m++ < ++n\n";
        cout << "Резултат = " << boolalpha << result << '\n';
        cout << "m = " << m2 << ", n = " << n2 << '\n';
    }

    // 3) n-- < --m
    {
        int m3 = m;
        int n3 = n;
        bool result = n3-- < --m3;

        cout << "\n3) n-- < --m\n";
        cout << "Резултат = " << boolalpha << result << '\n';
        cout << "m = " << m3 << ", n = " << n3 << '\n';
    }

    return 0;
}
