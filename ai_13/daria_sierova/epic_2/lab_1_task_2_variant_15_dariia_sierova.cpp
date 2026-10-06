#include <iostream>
#include <cmath>
using namespace std;

int main() {
    
    int n1 = 5, m1 = 10;
    int res1 = n1++ - m1;
    cout << " 1) n++ - m =" << res1 << "(після цього n=" << n1 << ", m=" << m1 << ")\n";

    int n2 = 5, m2 = 10;
    bool res2 = m2-- > n2;
    cout << " 2) m-- > n =" << res2 << "(після цього m=" << m2 << ", n=" << n2 << ")\n";
    
    int n3 = 5, m3 = 10;
    bool res3 = n3-- > m3;
    cout << " 3) n-- > m = " << res3 << " (після цього n=" << n3 << ", m=" << m3 << ")\n";

    return 0;
}
