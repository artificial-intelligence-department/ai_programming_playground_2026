/*
    Задача: Непередбачувана погода
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int i = 1;
    while (i <= n) {
        int a;
        cin >> a;
        if (a > 0) {
            cout << i << " ";
        }
        i++;
    }
    cout << endl;
    return 0;
}