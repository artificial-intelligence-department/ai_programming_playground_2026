// Алготестер Lab 2v1
// Стехнович Андрій ШІ-11
#include <iostream>
using namespace std;
void BubbleSort (int array[], int N) {;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N-1-i; j++) {
            if (array[j+1]<array[j]) {
                int b = array[j];
                array[j] = array[j+1];
                array[j+1] = b;
            }
            
        }
    }
}
int main() {
    int N;
    cin >> N;
    int r[N] = {0};
    for (int i = 0; i < N; i++) {
        cin >> r[i];
    }
    BubbleSort(r, N);
    if (N > 2) {
        int var_1 = r[N-1]-r[1];
        int var_2 = r[N-2]-r[0];
        cout << min(var_1, var_2) << endl;
    } else if (N == 2) {
        cout << min(r[0], r[1]) << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;

    
}