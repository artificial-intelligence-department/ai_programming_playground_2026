#include <iostream>
#include <climits>
using namespace std;
int main(){
    int n;
    cin >> n;
    int max = INT_MIN;
    int index = -1;
    for (int i = 0; i<n; i++) {
        int a;
        cin >> a;
        if (a>max) {
            max=a;
            index=i;
        }
    }
    cout << index <<endl;
    return 0;

}