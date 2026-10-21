#include <iostream>
using namespace std;

int main(){
    int k;
    int n;
    cin >> k >> n;
    int c[100];
    for(int i = 0; i < n; i++){
        cin >> c[i];
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(c[j] > c[j + 1]) {
            int t = c[j];
            c[j] = c[j + 1];
            c[j + 1] = t;
        }
    }
}
int count = 0;
for (int i = 0; i < n; i++){
    if(c[i] <= k){
        k = k - c[i];
        count++ ;
    }
    else {
        break;
    }

}
cout << count ;

    return 0;
}