//Задача 1401 - Road Crossing
//https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40670

#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int arr[n];
    int res = 0;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++){
        if (arr[i] % 2 == arr[i + 1] % 2) continue;
        else res++;
    }
    cout << res;
}