/*
    Алготестер. "Торт для Петрика"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float n = 0.0f; // amount of layers
    float r = 0.0f; // first layer radius
    float r_last = 0.0f; // last layer radius
    float S = 0.0f; // full area
    float S_last = 0.0f; // last layer area

    cin >> n;
    cin >> r;

    S = 3.141592*r*r;
    S_last = S/n;
    r_last = r/sqrt(n);
    cout << r_last << endl;
}