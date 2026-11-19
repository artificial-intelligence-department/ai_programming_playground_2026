#include <algorithm>
#include <iostream>

using namespace std;

void print_array(int* arr, int len)
{
    cout << len << endl;
    for (int i = 0; i < len; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main()
{
    int arr1[101], arr2[101], res[202];
    int n = 0, m = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr1[i];
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> arr2[i];

    sort(arr1, arr1 + n);
    sort(arr2, arr2 + m);

    int* res_end = set_difference(arr1, arr1 + n, arr2, arr2 + m, res);
    print_array(res, (int)(res_end - res));

    res_end = set_difference(arr2, arr2 + m, arr1, arr1 + n, res);
    print_array(res, (int)(res_end - res));

    res_end = set_intersection(arr1, arr1 + n, arr2, arr2 + m, res);
    print_array(res, (int)(res_end - res));

    res_end = set_union(arr1, arr1 + n, arr2, arr2 + m, res);
    print_array(res, (int)(res_end - res));

    res_end = set_symmetric_difference(arr1, arr1 + n, arr2, arr2 + m, res);
    print_array(res, (int)(res_end - res));

    return 0;
}