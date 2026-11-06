/*
Епік 5. Self Practice: Algotester, задача "Найкращий акумулятор"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <string>
using namespace std;

int main () {

    int n;
    cin >> n;

    char c;
    cin >> c;

    string min = "";

    for (int i = 0; i<n; i++) {

        string s;
        cin >> s;

        int j = 0;

        while (j < s.length() && s[j] <= c) {
            j++;
        }

        s.insert(j, 1, c);
        if (i == 0 || min > s) min = s;

    }

    cout << min << "\n";

    return 0;
}