#include <iostream>
using namespace std;

int main() {
    int n, k, count = 0, a, count_max = 0;
    cin >> n >> k;

    for(int i = 0; i < n; i++){
        cin >> a;
        if (a >= k){
            count++;
        } else {

            if (count > count_max){
                count_max = count;
            }

            count = 0; 
        }
    }
    
    if (count > count_max){
        count_max = count;
    }
    
    cout << count_max << endl;
    
    return 0;
}