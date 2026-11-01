/*Задача №0002 "Найбільша зростаюча підпослідовність"*/
#include <iostream>
using namespace std;
const int MAX_SIZE = 100;
int main(){
    int n;
    cin >> n;
    int a[MAX_SIZE];
    int poslidov[MAX_SIZE];
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    int maxcount = 0;
    for(int i=0; i<n; i++){
        poslidov[i] =1;
        for(int j=0; j<i; j++){
            if(a[j]<a[i] && poslidov[j]+1>poslidov[i]){
                poslidov[i]=poslidov[j]+1;
            }
        }
        if(poslidov[i]>maxcount){
            maxcount=poslidov[i];
        }
    }
    cout << maxcount<<endl;
    return 0;
}