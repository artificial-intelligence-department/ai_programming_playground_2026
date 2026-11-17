#include <iostream>
using namespace std;

int main()
{
    int n;
    int m;
    cin >> n >> m;
    int a[n] = {0};
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int b[m] = {0};
    for (int i = 0; i < m; i++){
        cin >> b[i];
    }
    
    int min_n = a[0];
    int min_m = b[0];
    
    for (int i = 1; i < n; i++){
        if (a[i] < min_n){
            min_n = a[i];
        }
    }
    for (int i = 1; i < m; i++){
        if (b[i] < min_m){
            min_m = b[i];
        }
    }
    cout << min_n + min_m << endl;
    return 0;
}
