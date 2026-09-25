#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
int main(){
    vector<int> x;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        x.push_back(a);
    }
    sort(x.begin(), x.end());
    int time = x[n-1] - x[0];
    cout << time << endl;
    
}

