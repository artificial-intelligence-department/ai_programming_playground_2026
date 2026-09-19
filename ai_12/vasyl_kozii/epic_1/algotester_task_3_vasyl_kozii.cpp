#include <iostream>
using namespace std;
int main()
{
    int a1, a2, a3, a4, a5;
    cin >>a1;
    cin >>a2;
    cin >>a3;
    cin >>a4;
    cin >>a5;
    if(a1<=0 || a2<=0 || a3<=0 || a4<=0 || a5<=0){
        cout <<"ERROR";
        return 1;
    }
    if(a2<=a1 && a3<=a2 && a4<=a3 && a5<=a4){
        cout <<"WIN";
    }
    else{
        cout <<"LOSS";
    }
    return 0;
}