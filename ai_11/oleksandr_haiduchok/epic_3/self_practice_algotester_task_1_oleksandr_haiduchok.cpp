#include <iostream>
using namespace std;
int main(){
    int n = 0;
    int k = 0;
    cin >> n;
    cin >> k;
    const int n1 = n;
    int a[n1];
    int count = 0;
    int maxcount = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int j = 0; j < n; j++){
        if(a[j] >= k){
            count++;
            if(count > maxcount){
                maxcount = count;
            }
        }
        else{
            count = 0;
        }
    
    }
 cout << maxcount;
 return 0;
}
