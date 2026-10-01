#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    bool pidv = true;
    bool zvych = true;
    for (int i = 0; i < n; i++) {
        int grade;
        cin >> grade;
        if (grade < 90)
            pidv = false;
        if (grade < 51)
            zvych = false;
    }
    if (pidv)
        cout << "Pidvyshchena";
    else if (zvych)
        cout << "Zvychaina";
    else
        cout << "Zabud pro stypendiiu";
    return 0;
}