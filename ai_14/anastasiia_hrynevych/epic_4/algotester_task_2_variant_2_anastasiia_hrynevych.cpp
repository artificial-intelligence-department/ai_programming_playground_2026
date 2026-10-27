#include <iostream>
using namespace std;


int main() {
    int N;
    cin >> N;
    int r[N];
    for (int i = 0; i < N; i++) {
    cin >> r[i];
    }
    int a, b, c;
    cin >> a >> b >> c;
    int newr[N];
    int sizenew = 0;
    for (int i = 0; i < N; i++) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            newr[sizenew] = r[i];
            sizenew++;
        }
        else continue;
    }
    if (sizenew == 0 || sizenew == 1) cout << "0\n";
    else {
        cout << sizenew - 1 << endl;
        for (int i = 1; i < sizenew; i++)
        cout << newr[i] + newr[i-1] << " ";
    }
}