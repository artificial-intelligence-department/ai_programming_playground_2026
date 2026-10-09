#include <iostream>
using namespace std;

int main() {
    int m;
    int n;
    cin >> m ;
    cin >> n;
    cout << --m-++n << endl;
    cout << (m * n < n++ )<< endl;
    cout << (n-- > m++ );

    return 0;   
}