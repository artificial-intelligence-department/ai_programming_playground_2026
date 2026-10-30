#include <iostream>
using namespace std;
int main(){
    int n, m;
    cin >>n>>m;
    string *matrix = new string[n];
    for (int i = 0; i<n; i++) {
        cin >> matrix[i];
    }
    bool rows[n] = {0};
    bool cols[m] = {0};
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) {
            if(matrix[i][j]=='1') {
                rows[i]=1;
                cols[j]=1;
            }
        }
    }
    delete[] matrix;
    matrix=nullptr;
    bool allrows=true;
    for (int i=0; i<n; i++) {
        if(!rows[i]) {
            allrows=false;
            break;
        }
    }
    bool allcols=true;
    for (int i=0; i<m; i++) {
        if(!cols[i]) {
            allcols=false;
            break;
        }
    }
    if (allrows or allcols) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;


}