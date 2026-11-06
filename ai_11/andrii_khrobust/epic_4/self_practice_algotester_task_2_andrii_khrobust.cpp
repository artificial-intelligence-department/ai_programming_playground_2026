/* №2106 Хробуст Андрій

*/
#include <iostream>
using namespace std;


int main() {
    int n;
    char a[1000][1000];
    cin >> n;
    for (int i = 0; i < n; i++) {
       cin>>a[i][0];
    }
    for (int i = 0; i < n; i++) {
       cin>>a[i][1];
    }
    for (int i = 0; i < n; i++) {
        if(a[i][0]=='1' && a[i][1]=='1'){
        cout<<"YES";
        return 0;
        }
    }
cout<<"NO";
    return 0;
}