
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;

    char x;
    int kolya_points = 0;
    int vasya_points = 0;
    int kolya_sets = 0;
    int vasya_sets = 0;

    for (int i = 0; i < n; i++) {
        cin >> x;

        if (x == 'K')
            kolya_points++;
        else
            vasya_points++;

    
        if ((kolya_points >= 11 || vasya_points >= 11) &&
            abs(kolya_points - vasya_points) >= 2) {

            if (kolya_points > vasya_points)
                kolya_sets++;
            else
                vasya_sets++;

            kolya_points = 0;
            vasya_points = 0;
        }
    }

    cout << kolya_sets << ":" << vasya_sets << endl;

    if (kolya_points > 0 || vasya_points > 0) {
        cout << kolya_points << ":" << vasya_points << endl;
    }

    return 0;
}

