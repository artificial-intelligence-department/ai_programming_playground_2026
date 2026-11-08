/*
Algotester Task 4 2 Variant 3
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
void merge(int arr[], int l, int m, int r, bool ascending) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[1005], R[1005];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (ascending) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
        } else {
            if (L[i] >= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void merge_sort(int arr[], int l, int r, bool ascending) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m, ascending);
        merge_sort(arr, m + 1, r, ascending);
        merge(arr, l, m, r, ascending);
    }
}
int my_partition(int arr[], int n, int rem) {
    int left[1005], right[1005];
    int l_cnt = 0, r_cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 3 == rem) {
            left[l_cnt++] = arr[i];
        } else {
            right[r_cnt++] = arr[i];
        }
    }
    for (int i = 0; i < l_cnt; ++i) arr[i] = left[i];
    for (int i = 0; i < r_cnt; ++i) arr[l_cnt + i] = right[i];
    return l_cnt;
}
int my_unique(int arr[], int n) {
    if (n == 0) return 0;
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    if (!(cin >> N)) return 0;
    int a[1005];
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    int cnt0 = my_partition(a, N, 0);
    int cnt1 = my_partition(a + cnt0, N - cnt0, 1);
    int cnt2 = N - cnt0 - cnt1;
    int* part0 = a;
    int* part1 = a + cnt0;
    int* part2 = a + cnt0 + cnt1;
    merge_sort(part0, 0, cnt0 - 1, true);
    merge_sort(part1, 0, cnt1 - 1, false);
    merge_sort(part2, 0, cnt2 - 1, true);
    cnt0 = my_unique(part0, cnt0);
    cnt1 = my_unique(part1, cnt1);
    cnt2 = my_unique(part2, cnt2);
    int M = 0;
    int res[1005];
    for (int i = 0; i < cnt0; ++i) res[M++] = part0[i];
    for (int i = 0; i < cnt1; ++i) res[M++] = part1[i];
    for (int i = 0; i < cnt2; ++i) res[M++] = part2[i];
    cout << M << "\n";
    for (int i = 0; i < M; ++i) {
        cout << res[i] << (i + 1 == M ? "" : " ");
    }
    cout << "\n";
}