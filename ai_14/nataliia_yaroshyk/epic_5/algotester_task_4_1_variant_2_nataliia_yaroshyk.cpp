#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N, K;
    cin >> N >> K;
    int a[N] = {};
    for(int i = 0; i < N; i++){
        cin >> a[i];
    }
    sort(a, a + N);

    int unique_count = unique(a, a + N) - a;
    
    K = K % unique_count;

    rotate(a, a + K, a + unique_count);

    cout << unique_count << "\n";
    for(int i = 0; i < unique_count; i++){
        cout << a[i] << " ";
    }
    return 0;
}