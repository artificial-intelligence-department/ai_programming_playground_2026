/*
    Алготестер. "There are two roads"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n = 0;
    int x_1 = 0;
    int y_1 = 0;
    int x_2 = 0;
    int y_2 = 0;
    int sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x_1;
        cin >> y_1;
        cin >> x_2;
        cin >> y_2;
        sum += sqrt(pow(x_2-x_1, 2)+pow(y_2-y_1, 2));
    }
    cout << sum;
    return 0;
}