#include <iostream>
using namespace std;

int main(){
    int N, a, b, c;
    cin >> N;
    int *arr= new int[N];

    for (int i = 0; i < N; i++){
        cin >> arr[i];
    }
    cin >> a >> b >> c;

    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] == a || arr[i] == b || arr[i] == c)
            count++;
    }

    if (N-count < 2)
    {
        cout << 0;
        return 0;
    }

    int *newArr = new int[N - count];

    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] == a || arr[i] == b || arr[i] == c) continue;

        newArr[counter] = arr[i];
        counter++;
    }

    delete[] arr;
    arr = nullptr;
    int *sumArr = new int[N - count - 1];

    counter = 0;
    for (int i = 0; i < N - count-1; i++)
    {
        sumArr[i] = newArr[i] + newArr[i + 1];
    }

    cout << N - count - 1 << endl;
    for (int i = 0; i < N - count - 1; i++)
    {
        cout << sumArr[i] << " ";
    }

    delete[] newArr;
    delete[] sumArr;
    newArr = nullptr;
    sumArr = nullptr;

    return 0;
}