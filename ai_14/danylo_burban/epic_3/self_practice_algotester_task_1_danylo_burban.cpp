/*Epic 3 - Зайчик і нетбук
Бурбан Данило
Ші - 14*/
#include <iostream>
#include <bitset>
using namespace std;
int main(){

    int n;
    int res=0;
    cin>>n;

    while (n>0){
        n=n>>1;
        res++;
    }
    cout<<res;
}