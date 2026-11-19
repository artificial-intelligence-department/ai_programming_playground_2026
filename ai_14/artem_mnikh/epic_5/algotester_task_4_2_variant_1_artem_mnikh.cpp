#include <algorithm>
#include <iostream>

using namespace std;

int* set_difference(int* arr1, int l1, int* arr2, int l2, int* result)
{
    int counter = 0, i = 0, j = 0;

    while (i < l1 && j < l2)
    {
        if (arr1[i] > arr2[j])
            j++;
        else if (arr1[i] < arr2[j])
            result[counter++] = arr1[i++];
        else
        {
            j++;
            i++;
        }
    }
    while (i < l1) result[counter++] = arr1[i++];
    return result + counter;
}

int* set_intersection(int* arr1, int l1, int* arr2, int l2, int* result)
{
    int counter = 0, i = 0, j = 0;
    while (i < l1 && j < l2)
    {
        if (arr1[i] > arr2[j])
            j++;
        else if (arr1[i] < arr2[j])
            i++;
        else
        {
            result[counter++] = arr1[i++];
            j++;
        }
    }
    return result + counter;
}

int* set_union(int* arr1, int l1, int* arr2, int l2, int* result)
{
    int counter = 0, i = 0, j = 0;
    while (i < l1 && j < l2)
    {
        if (arr1[i] > arr2[j])
            result[counter++] = arr2[j++];
        else if (arr1[i] < arr2[j])
            result[counter++] = arr1[i++];
        else
        {
            result[counter++] = arr1[i++];
            j++;
        }
    }
    while (i < l1) result[counter++] = arr1[i++];
    while (j < l2) result[counter++] = arr2[j++];
    return result + counter;
}

int* set_symmetric_difference(int* arr1, int l1, int* arr2, int l2, int* result)
{
    int u_arr[202], i_arr[101];
    int* u_end = set_union(arr1, l1, arr2, l2, u_arr);
    int* i_end = set_intersection(arr1, l1, arr2, l2, i_arr);

    int u_len = (int)(u_end - u_arr);
    int i_len = (int)(i_end - i_arr);

    return set_difference(u_arr, u_len, i_arr, i_len, result);
}

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
    int n, m;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr1[i];
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> arr2[i];

    sort(arr1, arr1 + n);
    sort(arr2, arr2 + m);

    int* res_end = set_difference(arr1, n, arr2, m, res);
    print_array(res, (int)(res_end - res));

    res_end = set_difference(arr2, m, arr1, n, res);
    print_array(res, (int)(res_end - res));

    res_end = set_intersection(arr1, n, arr2, m, res);
    print_array(res, (int)(res_end - res));

    res_end = set_union(arr1, n, arr2, m, res);
    print_array(res, (int)(res_end - res));

    res_end = set_symmetric_difference(arr1, n, arr2, m, res);
    print_array(res, (int)(res_end - res));

    return 0;
}