//Задача №2824 "Різноманітні букети"
#include <iostream>
using namespace std;
int main(){
    long long n, r, b;
    long long k=0;
    cin >> r >> b >> n;

    long long minRed = 0, maxRed;
    if(n-b>0) minRed = n-b;
    if(n<r) maxRed = n;
    else maxRed = r;

    for(long long i=1; i<=maxRed-minRed+1; i++){
        if((i*minRed + i*(i-1)/2 <= r) && (i*n - b <= i*maxRed - i*(i-1)/2) && (i*n - b <= r)){
            k++;
        } else {
            break;
        }
    }
    cout << k << endl;
    return 0;
}