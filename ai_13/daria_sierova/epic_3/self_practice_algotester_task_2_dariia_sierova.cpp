#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if (n >= 1 && n <=100 && m>= 1 && m <= 100){

        if ((n * m) % 2 == 1) {
            cout << "Imp" << endl;
        } else {
            cout << "Dragon" << endl;
        }
    } 
    return 0;
}