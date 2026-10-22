/* 
Алготестер, варіант 3
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    const int n = 5;
    long long a[n];
    for(int i = 0; i < n; i++){
    cin >> a[i];
    }

    for(int i = 0; i < n; i++){
        if (a[i] <= 0){
            cout << "ERROR" << endl;
            return 0;
        }
        if(i > 0 && a[i - 1] < a[i]){
            cout << "LOSS" << endl;
            return 0;
        } 
    }

    cout << "WIN" << endl;
    return 0;
}
