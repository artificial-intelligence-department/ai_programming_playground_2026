#include <iostream>

using namespace std;

int main(){

    int n, m;
    int t = 0;
    int f = 0;
    cin >> n;

    int* N = new int[n];
        for (int i = 0; i < n; i++){
            cin >> N[i];
        }
    
    cin >> m;

    int* M = new int[m];
        for (int i = 0; i < m; i++){
            cin >> M[i];
        }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (N[i] == M[j]){
                t++;
            }
        }
    }
    
    f = n + m - t;
    
    cout << t << endl;
    cout << f << endl;
    
    delete[] N;
    delete[] M;
    

return 0;
}




