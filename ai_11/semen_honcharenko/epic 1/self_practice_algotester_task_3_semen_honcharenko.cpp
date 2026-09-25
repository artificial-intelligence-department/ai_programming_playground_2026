/*
 * Epic_1 self practice Algotester task "Deputy's money"
 * semen_honcharenko
 * ai_11
 */
#include <iostream>

int main() {

    int total_bills = 0;
    long long n = 0; // long long for giant numbers
    int banknotes[] = { 500, 200, 100, 50, 20, 10, 5, 2, 1};
    std::cin >> n;

    for( int i = 0; i < 9; i++ ) {
        int bill = banknotes[i];
        int count = n / bill;
        if ( count > 0 ) {
            total_bills += count;
            n %= bill;
        }
    }

    std::cout << total_bills << std::endl;

    return 0;
}