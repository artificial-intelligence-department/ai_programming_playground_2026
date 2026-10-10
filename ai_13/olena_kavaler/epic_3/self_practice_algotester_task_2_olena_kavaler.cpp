
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <cmath> 

using namespace std;

int main() {
    int n;
    cin >> n; 

    int a[1000]; 
    int b[1000]; 

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    int answer = 0; 

    // Ігор вибирає, яке своє число a[i] залишити 
    for (int i = 0; i < n; ++i) {

        // петрик у відповідь залишає найближче до a[i] своє число
        // best = найменша відстань від a[i] до чисел петрика
        int best = abs(a[i] - b[0]); // спочатку відстань до першого числа
        for (int j = 1; j < n; ++j) {
            int diff = abs(a[i] - b[j]);
            if (diff < best) {
                best = diff; // знайшли ближче число петрика
            }
        }

        // ігор обирає те a[i], де best найбільший
        if (best > answer) {
            answer = best;
        }
    }

    cout << answer << "\n";
    
    return 0;
}