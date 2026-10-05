/* 
Algotester
Lab 1v3. 
Mykhailo Koval
AI-14   
*/
#include <iostream>

using namespace std;

#include <iostream>

using namespace std;

int main() {
    long long a1, a2, a3, a4, a5;
    cin >> a1 >> a2 >> a3 >> a4 >> a5;

    if (a1 <= 0) {
        cout << "ERROR\n";
    } else if (a2 <= 0) {
        cout << "ERROR\n";
    } else if (a2 > a1) {
        cout << "LOSS\n";
    } else if (a3 <= 0) {
        cout << "ERROR\n";
    } else if (a3 > a2) {
        cout << "LOSS\n";
    } else if (a4 <= 0) {
        cout << "ERROR\n";
    } else if (a4 > a3) {
        cout << "LOSS\n";
    } else if (a5 <= 0) {
        cout << "ERROR\n";
    } else if (a5 > a4) {
        cout << "LOSS\n";
    } else {
        cout << "WIN\n";
    }

    return 0;
}