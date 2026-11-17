#include <iostream>
using namespace std;


int main()
{

    int N, K;
    cin >> N >> K;
    int *arr = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < N - 1; ++i) 
    {
        int minIndex = i;
        for (int j = i + 1; j < N; ++j) 
        {
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j; 
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

    int k = 1;
    for (int i = 1; i < N; i++) {
        if (arr[i] != arr[k - 1]) {
            arr[k++] = arr[i];
        }
    }

    int diff = k;
    int *newArr = new int[diff];
    for (int i = 0; i < diff; i++) {
        newArr[i] = arr[i];
    }

    int *cleanArr = new int[diff];
    for (int i = 0; i < diff; i++) {
        cleanArr[i] = newArr[i];
    }

    if (diff > 0) {
        K = K % diff;

        int counter = K;
        for (int i = 0; i < diff - K; i++) {
            newArr[i] = cleanArr[counter++];
        }

        counter = diff - K;
        int i = 0;
        while (counter < diff) {
            newArr[counter++] = cleanArr[i];
            i++;
        }
    }

   cout << diff << "\n";
    for (int i = 0; i < diff; i++) {
        cout << newArr[i] << " ";
    }
    cout << "\n";
    delete[] arr;
    delete[] newArr;
    delete[] cleanArr;
    return 0;
}