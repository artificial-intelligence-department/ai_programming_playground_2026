/* Algotester Lab 1 Task 2 */

#include <iostream>

using namespace std;

long long find_max(long long a, long long b, long long c, long long d){
    long long max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;
    return max;
}

long long find_min(long long a, long long b, long long c, long long d){
    long long min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    if (d < min) min = d;
    return min;
}


int main (){
    
    long long h[4];
    long long d[4];

    for (int i = 0; i < 4; i++){
        cin >> h[i];
    }

    for (int i = 0; i < 4; i++){
        cin >> d[i];
    }

    for (int i = 0; i < 4; i++){
       if (d[i] > h[i]){
        cout << "ERROR" << endl;
        return 0;
       }
    }

    bool f = false;

    for (int i = 0; i < 4; i++){
        h[i] -= d[i];

        long long h_min = find_min(h[0], h[1], h[2], h[3]);
        long long h_max = find_max(h[0], h[1], h[2], h[3]);

        
        if (h_max >= h_min * 2) {
                f = true;
        }
    }

    if (!f and h[0] == h[1] and h[1] == h[2] and h[2] == h[3]){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    
    return 0;
    
}
