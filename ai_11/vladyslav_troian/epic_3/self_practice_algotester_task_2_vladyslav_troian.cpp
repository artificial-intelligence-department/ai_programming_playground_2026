#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    long a[n] = {0};
    long sum = 0;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] > 1){
            a[i] -= 1;
            sum += a[i];
        } else continue;
    }
    cout << sum << endl;
    return 0;
}