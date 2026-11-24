#include <iostream>

using namespace std;

int main(){
    int N, Q, i, j, t;
    cin >> N;
    char **a = new char*[N];
    for(i=0;i<N;i++){
        a[i] = new char[N];
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> a[i][j];
            a[i][j] -= '0';
        }
    }
    cin >> Q;
    int *x = new int[Q];
    int *y = new int[Q];
    for(i=0;i<Q;i++){
        cin >> x[i]; x[i]--;
        cin >> y[i]; y[i]--;
    }
    
    for(i=0;i<Q;i++){
        bool n[10] = {0,0,0,0,0,0,0,0,0,0};
        for(j=N+1;j<10;j++) n[j] = 1;
        t = N;
        if(a[x[i]][y[i]] == 0){
            for(j=0;j<N;j++){
                if (a[x[i]][j] != 0 && n[a[x[i]][j]] == 0) {
                    n[a[x[i]][j]] = 1; 
                    t--;
                }
                if (a[j][y[i]] != 0 && n[a[j][y[i]]] == 0) {
                    n[a[j][y[i]]] = 1;
                    t--;
                }
            }
            if(t != 0){
                cout << t << endl;
                for(j=1;j<10;j++){
                    if(n[j] == 0){
                        cout << j << " ";
                    }
                }
                cout << '\n';
            }
            else{cout << 0 << '\n';}
        }
        if(a[x[i]][y[i]] != 0){
            cout << "1" << endl;
            cout << (int)a[x[i]][y[i]] << endl;
        }
    }
    return 0;
}