#include <iostream>

int main(){

    int s,n;
    n=0;
    std::cin >> s;

    for (int i = 0; s>0; i++){
        if (s >= 500){
            s=s-500;
            n++;
        } else if(s>=200){
            s=s-200;
            n++;
        } else if(s>=100){
            s=s-100;
            n++;
        } else if(s>=50){
            s=s-50;
            n++;
        } else if(s>=20){
            s=s-20;
            n++;
        } else if(s>=10){
            s=s-10;
            n++;
        } else if(s>=5){
            s=s-5;
            n++;
        }else if(s>=2){
            s=s-2;
            n++;
        }else if(s>=1){
            s=s-1;
            n++;
        } else{
            std::cout<<"error";
        };
    };
    std::cout << n;
};