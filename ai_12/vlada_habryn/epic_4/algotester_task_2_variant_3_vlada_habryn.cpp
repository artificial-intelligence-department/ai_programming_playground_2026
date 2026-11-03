#include <iostream>
using namespace std;
int main() {
    int n;
    int a[1001];
    cin >> n;
    for (int i = 1; i <= n; i++) {
    cin >> a[i];
}
int left = 1;
int right = n;
while (right - left > 1) {
    left += a[left];
    right -= a[right];
}
cout << left << " " << right << endl;
if (left == right) {
    cout << "Collision" << endl;
}
else if (left > right) {
    cout << "Miss" << endl;
}
else {
    cout << "Stopped" << endl;
}
    return 0;
}