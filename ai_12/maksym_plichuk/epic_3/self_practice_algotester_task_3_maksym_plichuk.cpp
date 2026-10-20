#include <iostream>
#include <cmath>
using namespace std;

int main(){

    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    
    for (int i = 0; i < n-1; i++)
    {
        int minIndex = i;
        for (int j = i; j < n; j++)
        {
            if (arr[j]<arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }

    int midHouse = arr[n / 2];
    int minDistance = 0;

    for (int i = 0; i < n; i++){
        minDistance += abs(midHouse - arr[i]);
    }
    cout << minDistance;
    return 0;
}