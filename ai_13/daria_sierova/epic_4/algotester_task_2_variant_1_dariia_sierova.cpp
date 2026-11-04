#include <iostream>
using namespace std;

int main() {
    int N; // розмір масиву
    cin >> N;
    if (cin.fail() || N < 0) return 0;

    long long* r = new long long[N];
    for (int i = 0; i < N; i++){
        cin >> r[i];
    }

    if ( N <= 2){
        cout << 0 << endl;
        delete[] r;
        r = nullptr;
        return 0;
    }

    // сортування масиву
    for (int i = 0; i < N ; i++){
        for(int j = 0; j < N - i - 1; j++){
            if (r[j] > r[j + 1]){
                long long temp = r[j];
                r[j] = r [j+1];
                r[j + 1] = temp;
            }
        }
    }

    long long option1 = r[N-1] - r[1]; // викидаєм мінімум
    long long option2 = r[N - 2] - r[0]; //викидаєм максимум
    long long m;

    if (option1 < option2){
        m = option1;
    } else {
        m = option2;
    }
    cout << m << endl;

    delete[] r;
    r = nullptr; // обнулення вказівника
    return 0;
}