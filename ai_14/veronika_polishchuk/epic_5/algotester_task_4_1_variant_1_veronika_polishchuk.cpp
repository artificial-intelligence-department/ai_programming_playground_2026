// Алготестер, лабораторна 4 варіант 1, stl

#include <iostream>
#include <algorithm>

using namespace std;

void print(int arr[], int k) {
    cout << k << "\n";
    for (int x = 0; x < k; x++) cout << arr[x] << " ";
    cout << "\n\n";
}

int main(){
    int n, m;
    int a[100], b[100];

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
       cin >> b[i];
    }
    sort(a, a + n);
    sort(b, b + m);

    int res1[200];
    int* end1 = set_difference(a, a + n, b, b + m, res1);
    int k1 = end1 - res1;
    print(res1, k1);

    int res2[200];
    int* end2 = set_difference(b, b + m, a, a + n, res2);
    int k2 = end2 - res2;
    print(res2, k2);

    int res3[200];
    int* end3 =  set_intersection(a, a + n, b, b + m, res3);
    int k3 = end3 - res3;
    print(res3, k3);

    int res4[200];
    int* end4 =  set_union(a, a + n, b, b + m, res4);
    int k4 = end4 - res4;
    print(res4, k4);

    int res5[200];
    int* end5 =  set_symmetric_difference(a, a + n, b, b + m, res5);
    int k5 = end5 - res5;
    print(res5, k5);
    
    return 0;
}
