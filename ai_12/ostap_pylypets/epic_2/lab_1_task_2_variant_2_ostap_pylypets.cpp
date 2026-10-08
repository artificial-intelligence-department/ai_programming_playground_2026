#include <iostream>
using namespace std;
 int main() {
    int n, m;
    cout << "Введіть число n: ";
    cin >> n;
    cout << "Введіть число m: ";
    cin >> m;
    cout << (n+++m)<< " ";
    cout << ((m--)>n)<< " ";
    cout << ((n-- )>m)<< " ";

    return 0;
 }