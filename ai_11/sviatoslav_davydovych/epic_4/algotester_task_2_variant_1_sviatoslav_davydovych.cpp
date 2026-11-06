/* 
Lab 2v1
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int INT_MAX = 100000;
    const int INT_MIN = 0;

    int n;
    cin >> n;
    if (n==1){
        int empty;
        cin >> empty;
        cout << 0;
        return 0;
    }

    int min1 = INT_MAX, min2 = INT_MAX, max1 = INT_MIN, max2 = INT_MIN;
    for (int i = 0; i<n; i++){
        int current;
        cin >> current;

        if (current>=max1){
            max2 = max1;
            max1 = current;
        } else if(current>max2){
            max2 = current;
        }

        if (current<=min1){
            min2 = min1;
            min1 = current;
        } else if(current<min2){
            min2 = current;
        }
    }
    
    cout << fmin(max1-min2,max2-min1);

    return 0;
}