#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
    
    sort(vec.begin(), vec.end());
    
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    
    int moveTimes = K % vec.size();
    
    rotate(vec.begin(), vec.begin()+moveTimes, vec.end());
    cout << vec.size() << endl;
    for (int val : vec) {
        cout << val << " ";
    }
}
