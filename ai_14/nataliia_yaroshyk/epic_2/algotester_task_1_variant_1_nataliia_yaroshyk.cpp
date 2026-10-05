/*  Algotester
    Lab 1v1. 
    Наталія Ярошик
    ШІ-14   */
#include <iostream>
using namespace std;

int main(){
    long long H, M, h1, m1, h2, m2, h3, m3;
    cin >> H >> M;
    cin >> h1 >> m1;
    cin >> h2 >> m2;
    cin >> h3 >> m3;

        if((h1 != 0 && m1 != 0) || (h2 != 0 && m2 != 0) || (h3 != 0 && m3 != 0)){
            cout << "NO" << endl;
            return 0;
        }

    H = H - (h1 + h2 + h3);
    M = M - (m1 + m2 + m3);

    if(H > 0 && M > 0){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}