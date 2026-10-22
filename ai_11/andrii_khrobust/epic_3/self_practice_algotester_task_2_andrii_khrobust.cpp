/*Хробуст задача 0891
*/
#include <iostream>
using namespace std;
void bubbleSort(int a[],int n){
    for(int i=0;i<n-1;i++){
    for (int j=0;j<n-i-1;j++){
        if(a[j]>a[j+1]){
            int save=a[j];
            a[j]=a[j+1];
            a[j+1]=save;
        }

     }
     
}
}

int main(){
int n,m;
cin>>n;
cin>>m;
int a[1000];
int b[1000];
for(int i=0;i<n;i++){
    cin>>a[i];
}
bubbleSort(a,n);
for(int i=0;i<m;i++){
    cin>>b[i];
}
bubbleSort(b,m);
int sum=0;
sum=a[0]+b[0];
cout<<sum;
    return 0;
}
