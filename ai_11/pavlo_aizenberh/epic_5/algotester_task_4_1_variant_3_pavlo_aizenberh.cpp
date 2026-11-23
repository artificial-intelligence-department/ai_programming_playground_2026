    
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    auto first = partition(arr.begin(), arr.end(),[](int x) { return x % 3 == 0; });
    auto second = partition(first, arr.end(), [](int x) { return x % 3 == 1; });

    sort(arr.begin(), first);
    sort(first, second);
    reverse(first, second);
    sort(second, arr.end());

    auto last = unique(arr.begin(), arr.end());
    arr.erase(last, arr.end());

    cout << arr.size() << '\n';

    for (int x : arr) {
        cout << x << ' ';
    }
    
    cout << '\n';
    return 0;
}
