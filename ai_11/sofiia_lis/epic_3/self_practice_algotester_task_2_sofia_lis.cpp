/* 
Епік 3. self practice: Algotester, задача "Бомбардування"
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    long long arr_x[1000];
    long long arr_y[1000];    
    long long arr_R[1000];

    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> arr_x[i] >> arr_y[i] >> arr_R[i];
        if(arr_R[i] < 1) {
            cout << "Значення радіуса може бути від 1 до 1000";
        return 1;        
        }
    }

    int best = 0;
    
    for(int i = 0; i < n; i++) {
        int count = 0;
        for(int j = 0; j < n; j++) {
            if(i == j) {
                continue;
            }
            if(arr_R[i] < arr_R[j]) {
                continue;
            }
            long double distance = (sqrt(pow(arr_x[j] - arr_x[i], 2) + pow(arr_y[j] - arr_y[i], 2))) + arr_R[j];
            if(distance <= arr_R[i]) {
                count += 1;
            }
        }
        if(count > best) {
            best = count;
        }
    }

    cout << best;

    return 0;
}
