#include <iostream>
#include <string>
using namespace std;
int main() {
    int x,n,k;
    cin>>x>>n>>k;
    string result = "";
    int carry = 0;
    for(int i=0; i<n+k-1; i++) {
        int count = i+1;
        if(count > n){
            count = n;
        }
        if (count > k) {
            count = k;
        }
        if (count > n + k - i - 1) {
            count = n + k - i - 1;
        }
        int sum = x * count + carry;
        int digit = sum%10;
        carry = sum/10;
        result += char('0' + digit);
    }
    while (carry > 0){
        int digit = carry%10;
        result += char('0'+digit);
        carry = carry/10;
    }
    for (int i = result.length() - 1; i >= 0; i--) {
        cout<<result[i];
    }
    cout<<endl;
    return 0;
}
