#include <iostream>

using namespace std;
int sym = 0;
int trans(int l, int s, int** a) {
    if(a[l][s] != a[s][l]) sym = 1;
    if(l != s){
        int r;
        r = a[l][s];
        a[l][s] = a[s][l];
        a[s][l] = r;
    }
    return 0;
}

int main() {
    int n, i = 0, j =0;
    cin >> n;
    int **a = new int*[n];
    for(i=0;i<n;i++){
        a[i] = new int[n];
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin >> a[i][j];
        }
    }
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            trans(i, j, a);
        }
    }
    if(sym == 1){
        cout << "Симетричність: " << "ні." << endl;
    }
    else cout << "Симетричність: " << "так." << endl;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    for(i=0;i<n;i++){
        delete[] a[i]; 
    }
    delete[] a;
}