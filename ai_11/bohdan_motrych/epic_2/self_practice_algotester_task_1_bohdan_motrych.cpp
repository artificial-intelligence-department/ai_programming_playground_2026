#include <iostream>
using namespace std;

int main() {
    int lviv = 0, kyiv = 0, donetsk = 0, kharkiv = 0;

    if (cin >> lviv >> kyiv >> donetsk >> kharkiv) {
        int total = lviv + kyiv + donetsk + kharkiv;
        cout << total << endl;
    }

    return 0;
}