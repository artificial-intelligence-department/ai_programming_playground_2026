#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    vector<int> arr;

    cin >> N;
    for(int i = 0; i < N; i++) {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    int a , b, c;
    cin >> a >> b >> c;
    vector<int> vec;
    vec.reserve(N);
    for(int i = 0; i < N; i++) {
        if (arr[i] != a && arr[i] != b && arr[i] != c) {
            vec.push_back(arr[i]);
        }
    }
    if (vec.size() <= 1) {
        cout << 0 << "\n\n";
        return 0;
    }
    int n = vec.size() -1;
    cout << n << "\n";
    for(int i = 0; i < n; i++) {
        cout << vec[i] + vec[i+1] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}