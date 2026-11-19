/* 
Епік 5. algotester_task_4_1_variant_2
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    int * arr = new int[N];
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + N); //за стандартом вказуємо наступний, бо функція використовує не включно

    int * last = unique(arr, arr + N);

    N = last - arr;
    
    K %= N;

    rotate(arr, arr + K, last);

    cout << N << endl;

    for(int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;

    arr = nullptr;

    return 0;
}