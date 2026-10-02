#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    
    int a[100];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int p[100];
    for(int i = 0; i < n; i++){
        p[i] = 1;
    }
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            if (a[j] < a[i] && p[j] + 1 > p[i]){
                p[i] = p[i] + 1;
            }
        }
    }
    int best = p[0];
    for (int i = 1; i < n; i++){
        if (p[i] > best){
            best = p[i];
        }
    }
    cout << best;
    return 0;
}