
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
using namespace std;

// функція рахує, скільки пар, що дорівнює card
long long countPairs(long long card, long long a, long long b, long long c, long long d) {
    long long favorable = 0; 

    for (long long x = 1; x * x <= card; ++x) {

        // якщо card ділиться на x без остачі, то x дільник
        if (card % x == 0) {
            long long y = card / x; // x * y = card

            // варіант 1: Зеник каже x, Марічка каже y
            if (x >= a && x <= b && y >= c && y <= d) favorable++;

            // варіант 2: Зеник каже y, Марічка каже x 
            if (x != y && y >= a && y <= b && x >= c && x <= d) favorable++;
        }
    }
    return favorable; 
}

int main() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d; 

    int n;
    cin >> n; 

    // усі можливі пари
    long long total = (b - a + 1) * (d - c + 1);

    for (int i = 0; i < n; ++i) {
        long long card;
        cin >> card; 

        cout << countPairs(card, a, b, c, d) << "/" << total << "\n";
    }
    return 0;
}