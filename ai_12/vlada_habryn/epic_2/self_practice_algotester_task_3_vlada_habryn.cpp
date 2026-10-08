#include <iostream>
using namespace std;
int main(){
    int n;
    int m;
    int k;
    cin>>n>>m>>k;
    int total = n * k;
    if (total>m)
    cout<<total<<endl;
    else
    cout<<m<<endl;
    return 0;
}
