/*Epic 4 - lab 2v2
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main() {
    int N = 0;
    cin >> N;
    
    int r[N];
    for(int i = 0; i < N; i++){
        cin >> r[i];
    }
    
    int delete_nums[3];
    for(int i = 0; i < 3; i++){
        cin >> delete_nums[i];
    }
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < N; j++){
            if (delete_nums[i] == r[j]){
                for (int k = j; k < N - 1; k++) {
                r[k] = r[k + 1];
                }
            N--;
            j--;
            }
        }
    }
    
    int M = 0;
    if (N > 1){
        M = N - 1;
    } else {
        M = 0;
    }
    
    int array[M];
    
    for (int i = 0; i < M; i++){
        array[i] = r[i] + r [i + 1];
    }
    
    cout << M << endl;
    for (int i = 0; i < M; i++){
        cout << array[i] << " ";
    }
    return 0;
}