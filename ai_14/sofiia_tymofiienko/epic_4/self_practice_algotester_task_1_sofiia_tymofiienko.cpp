#include <iostream>
using namespace std;
int main(){
int n;
cin>>n;
int s;
int* a= new int[n];
for (int i=0; i<n; i++){
    cin>>a[i];
}
int m=a[0];
for (int i=0; i<n; i++){
    if (a[i]<m){
        m=a[i];
    }
}
if (m>=90){
    cout<<"Pidvyshchena"<<endl;
}else{
    if (m>=51){
        cout<<"Zvychaina"<<endl;
    }
    if (m<51){
     cout<<"Zabud pro stypendiiu"<<endl;
    }
}

delete[]a;
    return 0;
}