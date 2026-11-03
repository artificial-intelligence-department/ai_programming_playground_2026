#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    char **a = new char*[n];
    for(int i=0;i<n;i++){
        a[i] = new char[n]; 
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n;j++) {
            cin >> a[i][j];
        }
    }
    bool sym = true;
    for(int i = 0;i<n;i++) {
        char *row = a[i];
        for(int j=0; j<n; j++) {
            char *col = a[j];
            if(*(row + j) != *(col + i)){
                sym = false;
            }
            if(!sym) break;
        }
    }
    for(int i=0;i<n;i++){
        delete[] a[i];
    }
    delete[] a;
    if(sym) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
    return 0;
}