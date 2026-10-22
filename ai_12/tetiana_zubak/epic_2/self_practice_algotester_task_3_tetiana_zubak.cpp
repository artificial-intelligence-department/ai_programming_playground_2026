#include <iostream>

using namespace std;

int main(){
    int n;
    int sum = 0;
    cin >> n;
    int N[n];
    for(int i = 0; i < n; i++){
        cin >> N[i];
    }
    
    for(int i = 0; i < n - 1; i++){
        while(N[i] == N[i + 1]){
        N[i + 1]++;
        sum++;
    }
    }

    cout << sum << endl;
    return 0;
}