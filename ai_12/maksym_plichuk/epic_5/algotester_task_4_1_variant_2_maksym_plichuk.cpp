#include <iostream>
#include <algorithm>
using namespace std;


int main()
{

    int N, K;
    cin >> N >> K;
    int *arr = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + N);
    int* uniqueEnd = unique(arr, arr + N);

    int diff = uniqueEnd - arr;
    int *newArr = new int[diff];

    for (int i = 0; i < diff; i++)
    {
        newArr[i] = arr[i];
    }

    sort(newArr, newArr + diff);

    cout << diff << endl;
    if (diff > 0) {
        K = K % diff;
        rotate(newArr, newArr + K, newArr + diff);
    }
    
    for (int i = 0; i < diff; i++)
    {
        cout << newArr[i] << " ";
    }

    delete[] arr;
    delete[] newArr;
    return 0;
}