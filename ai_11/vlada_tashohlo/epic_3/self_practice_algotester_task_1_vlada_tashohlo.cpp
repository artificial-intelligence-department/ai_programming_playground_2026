
/* 
Епік 3. self practice: Algotester, задача "Факторіал"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
using namespace std;

int main() {
    long long n = 0;
    if (!(cin >> n)) return 0;
    long long cnt = 0;
    while (n > 0) {
        n /= 5;
        cnt += n;
    }
    cout << cnt;
    return 0;
}