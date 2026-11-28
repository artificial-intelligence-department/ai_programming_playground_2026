#include <iostream>

using namespace std;

int main(){
    unsigned long long matrix;
    int n,r,c;
    cin >> matrix >> n;

    for(int i = 0; i < n; i++){
        cin >> r >> c;
        r--;
        c--;
        for(int j = 0; j < 8; j++){
            matrix = matrix ^ (1ULL << r*8+j);
        }
        for(int k = 0; k < 8; k++){
            matrix  = (k == r) ? matrix : matrix ^ (1ULL << (8*k+c));
        }
    }

    cout << matrix;

    return 0;
}