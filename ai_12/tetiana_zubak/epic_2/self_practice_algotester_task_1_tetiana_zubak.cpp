#include <iostream>

using namespace std;

int main(){
    int n;
    long long sum = 0;
    cin >> n;
    int pack[100000];
    for(int i = 0; i < n; i++){
        cin >> pack[i];
        sum += --pack[i];
    }
    cout << sum << endl;

    return 0;
}