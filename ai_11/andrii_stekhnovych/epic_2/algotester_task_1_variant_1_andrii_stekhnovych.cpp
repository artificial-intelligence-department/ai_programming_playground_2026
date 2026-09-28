#include <iostream>
using namespace std;
int main() {
    bool res = 1;
    long long H, M;
    cin >> H;
    cin >> M;
    for (int i=0; i<3; i++) {
        long long h, m;
        cin >> h;
        cin >> m;
        H-=h;
        M-=m;
        if (h>0 and m>0) {
            res=false;
        }

    }
    if (H<=0 or M<=0) {
        res=false;
    }
    if (res) {
        cout << "YES"<<endl;
    } else {
        cout << "NO"<<endl;
    }
}