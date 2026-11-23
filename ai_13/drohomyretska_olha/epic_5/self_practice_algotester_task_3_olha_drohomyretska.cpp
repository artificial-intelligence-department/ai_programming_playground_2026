/*
Задача: Щасливі рядки
Автор: Ольга Дрогомирецька
Група: ШІ-13
*/
#include <iostream> 
#include <string>
using namespace std;

int main() {
    int n, m;
    string s, t;

    cin >> n >> m;
    cin >> s >> t;

    long long fourFirst = 0;
    long long sevenFirst = 0;
    long long fourSecond = 0;
    long long sevenSecond = 0;

    // Рахуємо четвірки та сімки в першому рядку.
    for (int i = 0; i < n; i++) {
    if (s[i] == '4') {
        fourFirst++;
    } else {
        sevenFirst++;
    }
}
    //рахуємо четвірки та сімки в другому рядку
    for (int i = 0; i < m; i++) {
        if (t[i] == '4') {
            fourSecond++;
        } else {
            sevenSecond++;
        }
    }
    //Усі способи вибрати префікс і суфікс, крім порожнього результату
    long long result = (n + 1LL) * (m + 1) - 1;
    //прибираємо повторні способи отримання однакових рядків
    result -= fourFirst * fourSecond;
    result -= sevenFirst * sevenSecond;

    cout << result << "\n";
    return 0;
}