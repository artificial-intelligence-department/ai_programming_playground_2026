#include <iostream>
using namespace std;

int main(){
    int n;
    int m;
    cout << " Enter n:";
    cin >> n;
    cout << " Enter m:";
    cin >> m;
    int result1 = n++ * m;
    cout << "Result 1: " << result1 << endl;
    bool result2 = n++ < m;
    cout << "Result 2: " << result2 << endl;
    int oldM = m;
    m--;
    bool result3 = oldM > m;
    cout << "Result 3: " << result3 << endl;
    return 0;
}