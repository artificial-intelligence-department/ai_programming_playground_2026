#include <iostream>

using namespace std;

int main(){

    int n;

    cin >> n;

    int* r = new int[n];
    int* u = new int[n];

    int a,b,c;

    for (int i = 0; i < n; i++){
        cin >> r[i];
    }

    cin >> a >> b >> c;

    int d = 0;

    for (int i = 0; i < n; i++){
        if (r[i] != a && r[i] != b && r[i] != c){
            u[d] = r[i];
            d++;
        }
    }

    if (d < 2){
        cout << 0;
    }
    else{
        cout << d - 1 << endl;
    }

    for (int i = 0; i < d - 1; i++){
        if (i > 0) { cout << " ";}
        cout << u[i]+u[i+1];
    }

return 0;
}
