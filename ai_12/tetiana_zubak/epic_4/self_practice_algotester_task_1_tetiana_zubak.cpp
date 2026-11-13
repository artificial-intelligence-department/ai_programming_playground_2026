#include <iostream>
#include <cmath>

using namespace std;

 long long first(long long p){
    long long k = sqrt((double)p);
    while(k * k < p) k++;
    while(k > 1 && (k - 1) * (k - 1) >= p) k--;
    return k;
 }

 char symbol(long long n){
    long long p = 1;
    long long lo = 1, len = 0;
    int d = 1;
    bool found = false;

    while(found == false){
        lo = first(p);
        long long hi = first(p * 10) - 1;
        len = (hi - lo + 1) * (d + 1);
        if(n <= len) found = true;
        else{
            n -= len;
            p *= 10;
            d++;
        }
    }

    long long k = lo + (n - 1) / (d + 1);
    int pos = (n - 1) % (d + 1);
    if(pos == d) return '*';

    long long num = k * k;
    for(int i = 0; i < d - 1 - pos; i++){
        num /= 10;
    }
    return '0' + num % 10;
 }

int main(){
    long long n = 0;
    cin >> n;
    cout << symbol(n) << endl;

    return 0;
}