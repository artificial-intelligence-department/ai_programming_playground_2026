#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int N, K, tmp;
    cin >> N >> K;

    int *mas = new int[N];

    for(int i = 0; i < N; i++){
        cin >> tmp;
        mas[i] = tmp;
    }

    sort(mas, mas + N);
    int count = unique(mas, mas + N) - mas;

    if (count > 0) {
        K = K % count;
        rotate(mas, mas + K, mas + count);
    }

    cout << count << endl;
    for(int i = 0; i < count; i++){
        cout << mas[i] << " ";
    }

    delete[] mas;
    return 0;
}