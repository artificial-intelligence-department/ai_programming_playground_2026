#include <iostream>
using namespace std;    

int main(){
    int l=1;
    int a=1000000000;
    while(true){
        int mid=l+(a-l)/2;
        cout<<mid<<"\n";
        char answer;
        cin>>answer;
        if(answer=='<'){
            l=mid+1;
        }
        else if(answer=='>'){
             a=mid-1;
        }
        else if(answer=='='){
            break;
        }
    }
    
    return 0;
}