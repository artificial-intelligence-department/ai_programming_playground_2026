#include <iostream>

using namespace std;
int main(){
    short int arr[1000]={0};
    short int  N =0;
    cin>>N;
    for (int i = 0; i<N; i++){
        cin>>arr[i];
    }
    short int loc_a=0;
    short int loc_b=N-1;
    short int speed_a = arr[0];
    short int speed_b = arr[N-1];
    
    if(loc_a==loc_b){
        cout<<loc_a+1<<" "<<loc_b+1<<"\nCollision";
        return 0;
    }
    
    if ((loc_a+1)==loc_b){
        cout<<loc_a+1<<" "<<loc_b+1<<"\nStopped";
        return 0;
    }
    for (short int i = 1, j = N-2; i<N; i++, j--){
    
        speed_a = arr[loc_a];
        speed_b = arr[loc_b];
        loc_a+=speed_a;
        loc_b-=speed_b;
        
        if(loc_a==loc_b){
            cout<<loc_a+1<<" "<<loc_b+1<<"\nCollision";
            return 0;
        }
        if (loc_a>loc_b){
            cout<<loc_a+1<<" "<<loc_b+1<<"\nMiss";
            return 0;
        }
        if ((loc_a+1)==loc_b){
            cout<<loc_a+1<<" "<<loc_b+1<<"\nStopped";
            return 0;
        }
    }
    return 0;

}