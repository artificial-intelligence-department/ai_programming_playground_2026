#include <iostream>
using namespace::std;
/* Алготестер лаб 2 варіант 2
   Сідлецький Тимофій ШІ-13
*/
int main () {
    int N;
    int r[100000];
    int N_new = 0;
    int r_new[100000];
    int a,b,c;

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> r[i];
    }
    cin >> a >> b >> c;

    for (int i = 0; i < N; i++) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            r_new[N_new++] = r[i];
        }
    }

    if (N_new > 0) {
        for (int i = 0; i < N_new - 1; i++) {
            r_new[i] = r_new[i] + r_new[i+1]; 
        }
        cout << N_new - 1 << endl;
        for (int i = 0; i < N_new - 1; i++) {
            cout << r_new[i] << " ";
        }
    } else {
        cout << "0";
    }

    return 0;
}