#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool hasRemainder0(int num){
    return num % 3 == 0;
}
bool hasRemainder1(int num){
    return num % 3 == 1;
}

int main(){

    int n;
    cin >> n;
    vector<int> a(n);

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    auto remainder1Start = partition(a.begin(), a.end(), hasRemainder0);
    auto remainder2Start = partition(remainder1Start, a.end(), hasRemainder1);
    
    sort(a.begin(), remainder1Start);
    sort(remainder1Start, remainder2Start, greater<int>());
    sort(remainder2Start, a.end());

    a.erase(unique(a.begin(), a.end()), a.end());
    
    cout << a.size() << endl;

    for(int i : a){
        cout << i << " ";
    }

    return 0;
}