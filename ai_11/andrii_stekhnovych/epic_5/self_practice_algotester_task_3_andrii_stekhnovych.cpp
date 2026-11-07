// Фібонета

#include <iostream>
using namespace std;


int main(){
    int n, a0, a1;
    cin >> n >> a0 >> a1;
    long long res=0;
    
    if (n==0) {
        res=a0;
    } else if (n==1) {
        res=a1;
    } else {
        long long prev = a0;
        long long curr = a1;
        for (long long i = 2; i<=n; i++) {
            if (prev<0 and curr<0) {
                res=-1;
                break;
            }
            if (prev>0 and curr>0) {
                res=1;
                break;
            }
            if (prev == 0 and curr == 0) {
                res=0;
                break;
            }
            long long next  = prev + curr;
            prev = curr;
            curr = next;
            res=curr;
        }
    }
    if (res>0) {
        cout << "+";
    } else if (res<0){
        cout << "-";
    } else {
        cout << "0";
    }
}