/*  
Задача: Self-practice. Завдання №3.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
#include <string>
using namespace std;

int min_hodiv[305][305];

int main() {
string s;
cin >> s;

string t = "";
for (int i = 0; i < (int)s.length(); i++) {
    if (i == 0 || s[i] != s[i - 1]) t += s[i]; //додаємо символ, якщо він перший або відрізняється від попереднього
}

int m = t.length();
if (m == 0) {
    cout << 0 << endl;
    return 0;}

for (int len = 1; len <= m; len++) {
    for (int i = 0; i + len - 1 < m; i++) {
        int j = i + len - 1;
        int best = 1;
        if (i + 1 <= j) best += min_hodiv[i + 1][j];
            for (int k = i + 1; k <= j; k++) {
                if (t[k] == t[i]) {
                    int mid = 0;
                    if (i + 1 <= k - 1) mid = min_hodiv[i + 1][k - 1];
                    int val = mid + min_hodiv[k][j];
                    if (val < best) best = val;}}
            min_hodiv[i][j] = best;}}

cout << min_hodiv[0][m - 1] << endl;
    return 0;
}