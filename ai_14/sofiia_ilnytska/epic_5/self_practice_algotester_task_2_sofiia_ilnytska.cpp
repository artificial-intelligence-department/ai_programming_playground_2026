/*
   Задача: Марічка вмикає лампи (алготестер)
   Ільницька Софія
   Група ШІ-14
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    double result = (double)(n + 1) / (n - k + 1);

    cout << setprecision(12) << result << endl;

    return 0;
}
