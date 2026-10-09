/*Algotester Lab 1v3
Лисюк Андріана
ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    long long previous = 0;
    long long current = 0;

    for (int i = 1; i <= 5; i++) {
        cin >> current;

        if (current <= 0) {
            cout << "ERROR\n";
            return 0;
        } 

        if (i > 1 && current > previous) {
            cout << "LOSS\n";
            return 0;
        }

        previous = current;
    }

    cout << "WIN\n";
    
    return 0;
}
