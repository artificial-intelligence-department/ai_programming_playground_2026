#include <iostream>
using namespace std;
int main(){
    int a, b, a1, b1, a2, b2, a3, b3;
    cin >>a >>b;
    cin >>a1 >>b1;
    cin >>a2 >>b2;
    cin >>a3 >>b3;
    if(a<0 || b<0 || a1<0 || a2<0 || a3<0 || b1<0 || b2<0 || b3<0){
        cout<<"Не вводьте від'ємні числа";
        return 1;
    }
    if(a1*b1==0 && a2*b2==0 && a3*b3==0 && (a-a1-a2-a3)>0 && (b-b1-b2-b3)>0 && (a1+b1)>0 && (a2+b2)>0 && (a3+b3)>0){
        cout<<"YES";
    }
    else{
        cout<<"NO";
    }
    return 0;
}