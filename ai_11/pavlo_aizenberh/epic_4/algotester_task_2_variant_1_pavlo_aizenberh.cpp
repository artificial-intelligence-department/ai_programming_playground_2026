#include <iostream>
using namespace std;

int main(){
    int N;
    cin >> N;
    if (N == 1){
        cout << 0;
        return 0;
    }
    int min1 = 2000000000, min2 = 2000000000;
    int max1 = -1, max2 = -1;
    for (int i = 0; i < N; i++){
        int x;
        cin >> x;
        
        if (x < min1){
            min2 = min1;
            min1 = x;
            }
        else if (x < min2) min2 = x;

        if (x > max1){
            max2 = max1;
            max1 = x;
            }
        else if (x > max2) max2 = x;
        }
    int opt1 = max1 - min2;
    int opt2 = max2 - min1;
    int ans = (opt1 < opt2) ? opt1 : opt2;
    cout << ans << endl;
    return 0;
} 
