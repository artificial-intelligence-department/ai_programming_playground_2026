#include <iostream>

using namespace std;


int main(){
    int n,m;
    cin >> n;
    int* mas1 = new int[n];
    for(int i = 0; i < n; i++){cin >> mas1[i];}
    cin >> m;
    int* mas2 = new int[m];
    for(int i = 0; i < m; i++){cin >> mas2[i];}

    int res = 0;
    for(int i = 0; i < n; i++){
        int a = mas1[i];
        for(int j = 0; j < m; j++){
            if(a == mas2[j]){res++;}
        }
    }

    cout << res << endl << m+n-res;

    delete[] mas1;
    delete[] mas2;
    return 0;
}