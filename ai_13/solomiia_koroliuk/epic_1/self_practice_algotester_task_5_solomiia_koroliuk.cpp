#include <iostream>

using namespace std;

int main (){
    
    long long H, M;
    
    cin >> H;
    cin >> M;

    cout << endl;

    long long h1, m1;
    long long h2, m2;
    long long h3, m3;

    cin >> h1 >> m1;
    cin >> h2 >> m2;
    cin >> h3 >> m3;

    if (h1>0 && m1>0 || h2>0 && m2>0 || h3>0 && m3>0){
        cout << "NO" << endl;
        return 0;
    }

    if ((H - (h1 + h2 + h3)) <= 0){
        cout << "NO" << endl;
        return 0;
    }

    if ((M - (m1 + m2 + m3)) <= 0){
        cout << "NO" << endl;
        return 0;
    }

    else{
        cout << "YES" << endl;
    }
    
    return 0;
    
}
