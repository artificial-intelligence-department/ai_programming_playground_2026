#include <iostream>
using namespace std;

void wat1(int &dron, int way[]){
   dron=dron+way[dron];
}
void wat2(int &dron, int way[]){
   dron=dron-way[dron];
}
int main(){
    int N=0;
    cin>>N;
    int way[N];

    for(int i=0;i<N;i++){
        cin>>way[i];
    }
    int dron1=0;
    int dron2=N-1;
    while(true){
        
        if(dron1==dron2){
            cout<<dron1+1<<" "<<dron2+1;
            cout<<"\nCollision";
            break;
        }
        
        if(dron1+1==dron2){
            cout<<dron1+1<<" "<<dron2+1;
            cout<<"\nStopped";
            break;
        }

        if(dron1>dron2){
            cout<<dron1+1<<" "<<dron2+1;
            cout<<"\nMiss";
            break;
        }
        wat1(dron1,way);
        wat2(dron2,way);
    }
    
 



    return 0;
}
