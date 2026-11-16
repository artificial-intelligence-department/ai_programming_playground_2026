#include <iostream>

using namespace std;


int myPartition(int a[], int n, int rem) {
    int left[1005];
    int right[1005];
    int l_cnt = 0, r_cnt = 0;


    for (int i = 0; i < n; ++i) {
        if (a[i] % 3 == rem) {
            left[l_cnt++] = a[i];
        } else {
            right[r_cnt++] = a[i];
        }
    }

    
    for (int i = 0; i < l_cnt; ++i) {
        a[i] = left[i];
    }
    for (int i = 0; i < r_cnt; ++i) {
        a[l_cnt + i] = right[i];
    }

    
    return l_cnt;
}


void myMerge(int arr[], int l, int m, int r, bool ascending) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[1005], R[1005];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    } 
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        bool condition;
        if (ascending) {
            condition = (L[i] <= R[j]);
        } 
        else {
            condition = (L[i] >= R[j]);
        }

        if (condition) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}


void mySort(int arr[], int l, int r, bool ascending) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mySort(arr, l, m, ascending);
        mySort(arr, m + 1, r, ascending);
        myMerge(arr, l, m, r, ascending);
    }
}


int myUnique(int arr[], int n) {
    if (n <= 0) return 0;

    int j = 0; 
    for (int i = 1; i < n; ++i) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1; 
}

int main() {
    
    int N;
    if (!(cin >> N)) return 0;

    int a[1005];
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    int cnt0 = myPartition(a, N, 0);                 
    int cnt1 = myPartition(a + cnt0, N - cnt0, 1);   
    int cnt2 = N - cnt0 - cnt1;                      

    int* part0 = a;
    int* part1 = a + cnt0;
    int* part2 = a + cnt0 + cnt1;

    if (cnt0 > 1) mySort(part0, 0, cnt0 - 1, true);   
    if (cnt1 > 1) mySort(part1, 0, cnt1 - 1, false);  
    if (cnt2 > 1) mySort(part2, 0, cnt2 - 1, true);   

    
    cnt0 = myUnique(part0, cnt0);
    cnt1 = myUnique(part1, cnt1);
    cnt2 = myUnique(part2, cnt2);

    
    int res[1005];
    int M = 0;

    for (int i = 0; i < cnt0; ++i) res[M++] = part0[i];
    for (int i = 0; i < cnt1; ++i) res[M++] = part1[i];
    for (int i = 0; i < cnt2; ++i) res[M++] = part2[i];

    
    cout << M << "\n";
    for (int i = 0; i < M; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}