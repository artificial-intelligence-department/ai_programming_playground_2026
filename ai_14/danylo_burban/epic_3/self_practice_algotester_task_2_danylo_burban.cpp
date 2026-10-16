/*Epic 3 - Існує дві дороги: Одна пряма, а інша …
Бурбан Данило
Ші - 14*/
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n=0;
    long res=0;
    short x1,y1,x2,y2;
    cin>>n;
    while (n>0){
        cin>>x1>>y1>>x2>>y2;
        res= res+(sqrt(pow((x2-x1),2)+pow((y2-y1),2)));
        n--;
    }
    cout<<res;
}