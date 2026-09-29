#include <iostream>
using namespace std;
 int main() {

    long long h[4];//legs
    long long d[4];//cut length
    long long minH=0, maxH=0;//shortest n longes leg to calc whether the table will fall
    int res = 0;

    for(int i=0; i<4; i++){ // read h, find min n max
        cin>>h[i];
        if(i==0){
            minH=h[i];
        }
        if(h[i]<minH){
            minH=h[i];
        }
    }

    for(int i=0; i<4;i++){ //read d
        cin>>d[i];
    }

    for(int i=0; i<4;){//"cut" the legs
        if(d[i]>h[i]){
            cout<<"ERROR";
            return 0;
        }

        h[i]=h[i]-d[i];
        minH = min(minH, h[i]);//cut

        for(int i=0; i<4;){
            maxH = max(maxH, h[i]);//find max
            i++;
        }
        if(maxH>=2*minH){// will it fall?
        res = 1;
        }
        maxH=0;
        i++;  
    }
    if(res==1){
        cout<<"NO";
    }
    if(res==0){
        cout<<"YES";
    }

    return 0;   

 }
