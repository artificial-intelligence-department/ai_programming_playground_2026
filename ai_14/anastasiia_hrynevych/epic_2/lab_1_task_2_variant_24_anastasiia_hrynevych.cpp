#include <iostream>
using namespace std;

int main() {
    int n, m; 
    cin >> n >> m;
    int res1 = n++*m;
    bool res2 = n++ < m;
    bool res3 = m-- > m;
    cout << "Результат 1: " << res1 << endl;
    cout << "Результат 2: " << res2 << endl;
    cout << "Результат 3: " << res3 << endl;
}