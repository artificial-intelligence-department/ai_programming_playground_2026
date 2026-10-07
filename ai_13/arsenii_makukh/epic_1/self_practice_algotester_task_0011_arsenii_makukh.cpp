#include <iostream>

using namespace std;

int main() {
    int packs;
    long long max_cookies = 0; 

    cout << "Кількість пачок печива: ";
    if (!(cin >> packs) || packs < 1) {
        return 0;
    }

    cout << "Кількість штук печива в пачках: ";
    for (int i = 0; i < packs; ++i) {
        long long cookies_in_pack;
        cin >> cookies_in_pack;

        if (cookies_in_pack > 0) {
            max_cookies += (cookies_in_pack - 1);
        }
    }

    cout << "Максимальна кількість штук печива: "
    << max_cookies << endl;

    return 0;
}
