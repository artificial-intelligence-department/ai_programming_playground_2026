#include <iostream>
using namespace std;

int main(){
    int n;
    int k;
    int a;
    int count_a = 0;
    int max_a = 0;

    cin >> n >> k;
    for(int i = 0; i < n; i++){
        cin >> a;
        if(a >= k){
        count_a++;
        if(count_a > max_a ){
            max_a = count_a;
        }        
     }
        else{
            count_a = 0;
        }
    }
       cout << max_a;

    return 0;
}