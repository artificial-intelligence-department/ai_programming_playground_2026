#include <iostream>

using namespace std;

int main(){
    int N;
    cin >> N;

    if(N > 1000 || N < 1){
        return 1;
    }

    int b = 0;
    int c = N - 1;

    int *a = new int[N];

    for(int i = 0; i < N; i++){
        cin >> a[i];

        if(a[i] < 1 || a[i] > 5){
            delete[] a;
            return 1;
        }
    }

    while(b + 1 < c){
        int left = *(a + b);
        int right = *(a + c);

        b += left;
        c -= right;
    }

    cout << b + 1 << " " << c + 1 << endl;

    if(b == c){
        cout << "Collision";
    }
    else if(b + 1 == c){
        cout << "Stopped";
    }
    else if(b > c){
        cout << "Miss";
    }

    delete[] a;
    return 0;
}
