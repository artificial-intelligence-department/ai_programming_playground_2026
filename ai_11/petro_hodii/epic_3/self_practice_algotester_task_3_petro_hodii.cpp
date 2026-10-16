#include <iostream>

using namespace std;

int main(){
    int n,k,a;
    int result = 0;
    int temp = 0;

    cin >> n >> k;

    for(int i = 0; i < n; i++){
        cin >> a;
        if(a >= k){
            temp++;
        }
        else{
            if(temp > result){
                result = temp;
            }
            temp = 0;
        }
    }

    if(result > temp){
        cout << result;
    }
    else{
        cout << temp;
    }

    return 0;
}