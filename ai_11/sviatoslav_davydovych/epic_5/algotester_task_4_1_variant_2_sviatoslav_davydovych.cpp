#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;
    vector<int> numbers(N);

    for (int i = 0; i<N; i++){
        cin >> numbers[i];
    }
    sort(numbers.begin(), numbers.end());

    vector<int>::iterator endID = unique(numbers.begin(), numbers.end());
    numbers.erase(endID, numbers.end());
    int newSize = numbers.size();
    K = K % newSize;

    rotate(numbers.begin(), numbers.begin()+K, numbers.end());
    
    cout << newSize << "\n";
    for (int i = 0; i<newSize; i++){
        cout << numbers[i] << " ";
    }
}
