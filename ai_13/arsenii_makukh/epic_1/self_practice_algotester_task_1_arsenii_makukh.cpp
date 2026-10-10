/*
Назва: Марічка і печиво
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int packs;
    long long max_cookies = 0; 

    if (!(cin >> packs) || packs < 1) {
        return 0;
    }

    for (int i = 0; i < packs; ++i) {
        long long cookies_in_pack;
        cin >> cookies_in_pack;

        if (cookies_in_pack > 0) {
            max_cookies += (cookies_in_pack - 1);
        }
    }

    cout << max_cookies << endl;

    return 0;
}