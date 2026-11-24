#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;
int main() {
    int N, K;
    cin >> N >> K;
    vector<int> a(N);
    for(int &x : a){
        cin >> x;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    
    int m = a.size();
    rotate(a.begin(), a.begin() + K % m, a.end());

    cout << m << '\n';
    for(int x : a) {
        cout << x << " ";
    }
    return 0;
}