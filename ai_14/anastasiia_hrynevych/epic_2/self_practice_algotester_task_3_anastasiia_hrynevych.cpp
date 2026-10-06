#include <iostream>
#include <cmath>
using namespace std;

int main() {
int n, minq = 0; long long min = 100000000;
cin >> n;
for (int i = 0; i < n; i++) {
long long a, b; cin >> a >> b;
long long d = a * a + b * b;
if (d < min) { min = d; minq = 1; }
          else if (d == min) minq++;
    }
    cout << minq << endl;
} 
