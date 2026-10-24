#include <iostream>
using namespace std;
const int MAX = 100001;
int sum[MAX];
int suma(int l, int r){
    
    return sum[r] - sum[l - 1];

}

int main(){
int n = 0;
int m = 0;
int l = 0;
int r = 0;
int i = 0;
int d = 0;
cin >> n;
cin >> m;
int num [MAX];
for( int p = 1; p <= n; p++){
    cin >> num[p];
    sum[p] = sum[p - 1] + num[p];
}

int p = 1;
while(p <= m){
    int t = 0;
    cin >> t;
    if (t == 1){
        cin >> l >> r;
cout << suma( l, r) << "\n";
    }
    if(t == 2){
        cin >> i >> d; 
        num[i] += d;
        for(int j = i; j <= n; j++){
            sum[j] += d;
        }
    }
    p++;
}
return 0;

}
