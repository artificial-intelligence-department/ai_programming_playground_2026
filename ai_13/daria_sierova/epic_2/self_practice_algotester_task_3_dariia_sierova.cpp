#include <iostream>
using namespace std;

int main() {
    int Lviv;
    int Kyiv;
    int Donetsk;
    int Kharkiv;

    cin >> Lviv >> Kyiv >> Donetsk >> Kharkiv;
    int sum = Lviv + Kyiv + Donetsk + Kharkiv;

    if (Lviv >= 0 && Lviv <= 1000 && Kyiv >= 0 && Kyiv <= 1000 && 
        Donetsk >= 0 && Donetsk <= 1000 && Kharkiv >= 0 && Kharkiv <= 1000) {
        cout << sum;
    } else {
        cout << "Error";
    }

    return 0;
}