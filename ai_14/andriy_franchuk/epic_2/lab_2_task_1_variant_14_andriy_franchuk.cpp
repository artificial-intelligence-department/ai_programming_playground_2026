#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n, m = 0;
    cin >> n >> m;

    cout << (m+--n) << endl;
    cout << (m++<++n) << endl;
    cout << (n--< --m) << endl;
    return 0;
}