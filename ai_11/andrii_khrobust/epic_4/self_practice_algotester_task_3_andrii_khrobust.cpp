/* №1893 Хробуст Андрій

*/
#include <iostream>
using namespace std;
 
int main(){
    int n,m ,k;
    cin>>n>>m>>k;
    char a[1000][1000];
    for(int i=0;i<n;i++){
          for(int j=0;j<m;j++){
           cin>>a[i][j];
          }
    }
    int count=0;
    for(int i=0;i<n;i++){
         int starsCount=0;
          for(int j=0;j<m;j++){
            if (a[i][j]=='*'){
             starsCount++;
            }
          }
          if(starsCount>k){
             int x=starsCount/k;
             if(starsCount %k==0)
             count=count+x;
             else 
             count=count+x+1;
            }
           else if(starsCount>0 && starsCount<=k)
           count++;
    }
cout<<count;
return 0;
}