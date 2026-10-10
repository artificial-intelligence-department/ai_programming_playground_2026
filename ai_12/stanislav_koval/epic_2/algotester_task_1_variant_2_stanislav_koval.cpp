#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long h[4];
    for (int i = 0; i < 4; i++){
        cin >> h[i];
    } 

    long long d[4];
    for (int i = 0; i < 4; i++){
        cin >> d[i];
    }

    for (int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            cout << "ERROR" << endl;
            return 0;
        }
    }

    int upside_down=0;

    for (int i = 0; i < 4; i++) {
        h[i]=h[i]-d[i];
        long long max_el = *max_element(h, h+4);
        long long min_el = *min_element(h, h+4);
        if (max_el>=2*min_el){
            upside_down=1;
        }
    }
    
    long long max_el = *max_element(h, h+4);
    long long min_el = *min_element(h, h+4);

    if (upside_down !=1 && max_el==min_el){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
}