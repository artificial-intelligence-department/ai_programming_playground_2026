#include <iostream>
using namespace std;
int main(){
    int sec, min, price_0 = 11, price_1 = 9, price_2 = 5, sum;
    cin>>sec;
    if(sec%60==0){
        min=sec/60;
    }else{
        min=sec/60 + 1;
    }
    if (min<=7){
        sum = price_0 + price_1*min;
    }else{
        sum = price_0 + price_1*7 + price_2*(min-7);
    }
    cout<<sum;


    return 0;
}