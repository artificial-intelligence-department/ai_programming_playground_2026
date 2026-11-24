#include <iostream>
#include <cmath>
using namespace std;

int distance(int x0 ,int y0, int x, int y){
    return abs(x-x0)+abs(y-y0);
}


int searchMax(int n, int m, int x, int y){
    int max=distance(1,1,x,y);
    int rightUp=distance(n,1,x,y);
    if(rightUp>max) max=rightUp;
    int leftDown=distance(1,m,x,y);
    if(leftDown>max) max=leftDown;
    int RightDown=distance(n,m,x,y);
    if(RightDown>max) max=RightDown;
    return max;
}




int main(){
    int n,m;
    cin>>n>>m;
    int **mas=new int*[n];
    for(int i=0;i<n;i++){
        mas[i]=new int[m];
    }
    int x,y;
    cin>>x>>y;
    int max=searchMax(n,m,x,y);
    mas[x-1][y-1]=max;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            mas[i][j]=max-distance(i+1,j+1,x,y);
            cout<<mas[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    return 0;
}