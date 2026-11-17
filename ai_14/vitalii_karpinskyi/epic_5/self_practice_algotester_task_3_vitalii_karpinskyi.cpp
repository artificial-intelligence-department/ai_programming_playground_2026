/*
Задача: Вакцина від реп'яховіруса
Карпінський Віталій
ШІ-14
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s, t;
    cin >> s;
    cin >> t;

    int n = s.length();

    cout << n << endl;

    for (int i = 0; i < n; i++) {
        char need = t[i];
        int index = 0;
        while (s[index] != need) {
        index++;
        }

        cout << index + 1 << " ";
        
        s.erase(index, 1);
        s += need;
    }

    return 0;
}