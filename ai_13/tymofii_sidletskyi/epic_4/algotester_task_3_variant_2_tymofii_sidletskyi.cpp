#include <iostream>
using namespace::std;
/* Алготестер лаб 3 варіант 2
   Сідлецький Тимофій ШІ-13
*/

int main () {
    int N, M;
    const int max_size = 100;
    int arr1[max_size];
    int arr2[max_size];
    int sim_count = 0;
    
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr1[i];
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> arr2[i];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (arr1[i] == arr2[j]) {
                sim_count++;
                continue;
            }
        }
    }
    cout << sim_count << endl;
    cout << N + M - sim_count;
    
    return 0;
}