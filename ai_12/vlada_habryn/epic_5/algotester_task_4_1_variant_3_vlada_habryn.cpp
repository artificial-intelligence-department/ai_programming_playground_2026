#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    int n;
    cin>>n;
    vector<int> a(n);
    for (int i = 0; i<n; i++){
        cin>>a[i];
    }
    vector<int> a0, a1, a2;
    for (int i = 0; i<n; i++){
        if (a[i]%3==0){
            a0.push_back(a[i]);
        }
        else if(a[i]%3==1){
            a1.push_back(a[i]);
        }
        else {
            a2.push_back(a[i]);
            
        }
    }
    sort(a0.begin(), a0.end());
    sort(a1.begin(), a1.end(), greater<int>());
    sort(a2.begin(), a2.end());
    a0.erase(unique(a0.begin(), a0.end()), a0.end());
    a1.erase(unique(a1.begin(), a1.end()), a1.end());
    a2.erase(unique(a2.begin(), a2.end()), a2.end());
    vector<int> result;
    result.insert(result.end(), a0.begin(), a0.end());
    result.insert(result.end(), a1.begin(), a1.end());
    result.insert(result.end(), a2.begin(), a2.end());
    cout<<result.size()<<endl;
    for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
}
    return 0;
}
