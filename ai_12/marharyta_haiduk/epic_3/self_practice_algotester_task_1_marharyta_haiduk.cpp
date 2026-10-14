/*
    Задача: Марічка і печиво
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (a > 0) 
        {
            sum += a - 1;
        }
    }
    cout << sum << endl;
    return 0;
}