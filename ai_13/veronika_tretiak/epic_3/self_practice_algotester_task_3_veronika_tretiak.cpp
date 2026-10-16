#include <iostream>

using namespace std;

int main(){
    int n;
    long long k;
    cin >> n >> k;

    int a[100000];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    int count = 0;
    int answer = 0;

    for(int i = 0; i < n; i++){
        if(a[i] >= k){
            count++;

            if(count > answer){
                answer = count;
            }
        }
        else {
            count = 0;
        }
    }
    cout << answer << '\n';
    return 0;
}