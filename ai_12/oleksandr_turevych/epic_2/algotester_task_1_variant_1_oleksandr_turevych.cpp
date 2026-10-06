/* Задача: Algotester lab 1v1
* Туревич Олександр
* Група ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
	long long H, M;
	cin >> H >> M;

    long long h1, m1, h2, m2, h3, m3;
    cin >> h1 >> m1 >> h2 >> m2 >> h3 >> m3;

    if (h1 > 0 && m1 > 0 || h2 > 0 && m2 > 0 || h3 > 0 && m3 > 0) {
        cout << "NO\n";
        return 0;
    } 
    else if ( h1+h2+h3 >= H || m1+m2+m3 >= M) {
        cout << "NO\n";
    } 
    else {
        cout << "YES\n";
    }


	return 0;
}
