#include <iostream>
#include <cmath>
using namespace std;
long long minimum(long long h1,long long h2,long long h3,long long h4){
        long long current = h1;
        if (h2<current) current=h2;
        if (h3<current) current=h3;
        if (h4<current) current=h4;
        return current;


    } 
    long long max(long long h1,long long h2,long long h3,long long h4) {
        long long current = h1;
        if (h2>current) current=h2;
        if (h3>current) current=h3;
        if (h4>current) current=h4;
        return current;


    } 
int main() {
    long long h1, h2, h3, h4;
    cin >> h1 >> h2 >> h3 >> h4;
    long long d1, d2, d3, d4;
    cin >> d1;
    cin >> d2;
    cin >> d3;
    cin >> d4;   
    if ((d1>h1)||(d2>h2)||(d3>h3)||(d4>h4)) {
        cout << "ERROR";
        return 0;
    } else {
        bool fell = false;
        h1-=d1;
        long long min_l= minimum(h1, h2, h3, h4);
        long long max_l= max(h1, h2, h3, h4);
        if (max_l>=2*min_l) {
            fell=true;
        }
        h2-=d2;
        min_l= minimum(h1, h2, h3, h4);
        max_l= max(h1, h2, h3, h4);
        if (max_l>=2*min_l) {
            fell=true;
        }
        h3-=d3;
        min_l= minimum(h1, h2, h3, h4);
        max_l= max(h1, h2, h3, h4);
        if (max_l>=2*min_l) {
            fell=true;
        }
        h4-=d4;
        min_l= minimum(h1, h2, h3, h4);
        max_l= max(h1, h2, h3, h4);
        if (max_l>=2*min_l) {
            fell=true;
        }
        if (!fell && (min_l==max_l)) {
            cout << "YES"; 
        } else {
            cout << "NO";
        }
        
    }
}