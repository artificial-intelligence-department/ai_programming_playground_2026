/* 
Задача: Algotester Self-Practice №3.
Автор: Дячок Маргарита.
Група: ШІ-14
*/
#include <iostream>
using namespace std;

int main() {
    
    int n;
    int counts[10] = {0};
    int counts_max[10] = {0};
    if (!(cin >> n)) return 0;

    while (n > 0) {
        int last = n % 10;
        counts[last]++;
        counts_max[last]++;
        n = n / 10;
    }

    int first_last = -1;
    for (int i = 1; i <= 9; i++) {
        if (counts[i] > 0) {
            first_last = i;
            break;
        }
    }

    cout << first_last;
    counts[first_last]--;

    while (counts[0] > 0) {
        cout << 0;
        counts[0]--;
    }

    for (int i = 1; i <= 9; i++) {
        while (counts[i] > 0) {
            cout << i;
            counts[i]--;
        }
    }

    cout << " ";

    for (int i = 9; i >= 0; i--) {
        while (counts_max[i] > 0) {
            cout << i;
            counts_max[i]--;
        }
    }
    cout << "\n";

    return 0;
}
