/*
Назва задачі: Lab 4v2
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &value : arr) {
        cin >> value;
    }

    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());

    if (!arr.empty()) {
        long long first = arr[k % arr.size()];
        
        auto middle = partition(arr.begin(), arr.end(), [first](long long value) {
            return value >= first;
        });
        sort(arr.begin(), middle);
        sort(middle, arr.end());
    }

    cout << arr.size() << '\n';
    for (int i = 0; i < (int)arr.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';
    return 0;
}