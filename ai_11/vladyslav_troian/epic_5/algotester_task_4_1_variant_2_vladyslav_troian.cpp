#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int rnum;
    cin >> rnum;

    int *a = new int[N];
    for (int i = 0; i < N; i++){
        cin >> a[i];
    }

    sort(a, a + N);
    int *last = unique(a, a + N);
    N = last - a;
    rnum %= N;
    rotate(a, a + rnum, a + N);

    cout << N << endl;
    for (int i = 0; i < N; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    delete[] a;
}