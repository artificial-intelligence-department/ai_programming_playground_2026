/* Задача на Алготестер Хелловін
Онишко Даніель ШІ-14
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int min_a = 1001; // За обмеженнями ціни не перевищують 1000
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        if (val < min_a) {
            min_a = val;
        }
    }

    int min_b = 1001;
    for (int i = 0; i < m; ++i) {
        int val;
        cin >> val;
        if (val < min_b) {
            min_b = val;
        }
    }

    
    cout << (min_a + min_b) << "\n";

    return 0;
}