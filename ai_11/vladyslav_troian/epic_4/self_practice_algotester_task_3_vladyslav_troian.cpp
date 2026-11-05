#include <iostream>
using namespace std;

void max(int *d_arr, int lenght)
{
    int max = *d_arr;
    for (int i = 0; i < lenght; i++){
        if (max < *(d_arr + i)){
            max = *(d_arr + i);
        }
    }
    cout << max << endl;
    delete[] d_arr;
}   

void max_arr(int *a, int N)
{
    int *dp = new int[N]();
    for (int k = 0; k < N; k++){
        *(dp + k) += 1;
    }
    for (int i = 1; i < N; i++){
        int dp_max = 0; 
        for (int j = 0; j < i; j++){ 
            if (*(a + j) < *(a + i) && *(dp + j) > dp_max){ // Перевіряємо чи є число продовженням минулих послідовностей
                dp_max = *(dp + j); // Зберігаємо номер останнього елемента який був у цій послідовності
            }
        }
        *(dp + i) = dp_max + 1; // Після перевірки додаємо 1 як наступний елемент послідовності
    }
    max(dp, N);
}

int main()
{
    int n;
    cin >> n;
    if (n > 100 || n < 1) return -1;
    int *all = new int[n];
    for (int i = 0; i < n; i++){
        cin >> all[i];
    }
    max_arr(all, n);
    delete[] all;
    return 0;
}