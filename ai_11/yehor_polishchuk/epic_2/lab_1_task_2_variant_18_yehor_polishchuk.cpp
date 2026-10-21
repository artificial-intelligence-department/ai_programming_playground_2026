#include <iostream>
using namespace std;

int main() {
    cout << "Введіть число n: ";
    int n;
    cin >> n;
    
    cout << "Введіть число m: ";
    int m;
    cin >> m;

    cout << "1) n++*m = " << n++*m << endl;

    cout <<boolalpha; 
    cout << "2) n++<m = " << (n++<m) << endl;
    cout << "3) m-->m = " << (m-->m) << endl;
    return 0;
}