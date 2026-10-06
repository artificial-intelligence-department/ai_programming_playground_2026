#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int m, n = 0;
    cin >> m >> n;

    cout << (m+--n) << endl;
    cout << (m++<++n) << endl;
    cout << (n--< --m) << endl;

    return 0;
}