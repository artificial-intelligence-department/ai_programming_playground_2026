/* 
Завдання з контесту, варіант 2, лабараторна 1
Белаш Матвій Валерійович
ШІ-12
*/
#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    long long h1, h2, h3, h4, d1, d2, d3, d4;

    cin >> h1 >> h2 >> h3 >> h4;
    cin >> d1;
    cin >> d2;
    cin >> d3;
    cin >> d4;

    if(h1 < d1 || h2 < d2 || h3 < d3 || h4 < d4){
        cout << "ERROR";
        return 0;
    }

    long long v1;
    long long v2;
    long long v3;
    long long v4;

    v1 = h1 - d1;

    long long maxh = max({v1, h2, h3 ,h4});
    long long minh = min({v1, h2, h3 ,h4});

    if(maxh >= 2 * minh){
        cout << "NO";
        return 0;
    }

    v2 = h2 - d2;

    maxh = max({v1, v2, h3 ,h4});
    minh = min({v1, v2, h3 ,h4});

    if(maxh >= 2 * minh){
        cout << "NO";
        return 0;
    }

    v3 = h3 - d3;

    maxh = max({v1, v2, v3 ,h4});
    minh = min({v1, v2, v3 ,h4});

    if(maxh >= 2 * minh){
        cout << "NO";
        return 0;
    }

    v4 = h4 - d4;

    maxh = max({v1, v2, v3 ,v4});
    minh = min({v1, v2, v3 ,v4});

    if(maxh >= 2 * minh){
        cout << "NO";
        return 0;
    }

    if( v1 == v2 && v2 == v3 && v3 == v4){
        cout << "YES";
    }
   

    return 0;

  

}