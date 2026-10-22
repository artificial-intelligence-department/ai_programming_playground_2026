/*Хробуст задача 0531
*/
#include <iostream>
using namespace std;

int main() {
int k,n;
cin>>k>>n;
int c[100];
int sum=0;
int j=0;
for (int j=0;j<n;j++){
    cin>>c[j];
}
for (int i=0;i<n-1;i++) {
        for (int j=0;j<n-i-1;j++) {
            if (c[j]>c[j+1]) {
                int save=c[j];
                c[j]=c[j+1];
                c[j+1]=save;
            }
        }
    }
    while(j<n && sum+c[j]<=k){
        sum +=c[j];
        j++;
    }
    cout<<j;
    return 0;
}