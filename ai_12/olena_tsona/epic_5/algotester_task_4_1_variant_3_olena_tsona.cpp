#include <iostream>
#include <vector>     
#include <algorithm>  

using namespace std;

bool myCompare(int a, int b) {
    int remA = a % 3;
    int remB = b % 3;

    if (remA != remB) {
        return remA < remB; 
    }

    if (remA == 0) {
        return a < b; 
    } 
    else if (remA == 1) {
        return a > b; 
    } 
    else {
        return a < b; 
    }
}

int main() {
    
    int n;
    if (!(cin >> n)) return 0;

 
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end(), myCompare);

    auto it = unique(arr.begin(), arr.end());

    arr.erase(it, arr.end());

    cout << arr.size() << "\n";

    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}