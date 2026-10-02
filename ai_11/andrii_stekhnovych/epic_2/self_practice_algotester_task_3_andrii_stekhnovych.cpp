#include <iostream>
using namespace std;
int main(){
    long l,w,u,d;
    cin >> l;
    cin >> w;
    cin >> u;
    cin >>d;
    long h = u+d;
    if (w>=l && h>=l) {
        cout << "Three times Sex on the Beach, please!";
    } else {
        cout << "Forget about the cocktails, man!";
    }
    return 0;
}