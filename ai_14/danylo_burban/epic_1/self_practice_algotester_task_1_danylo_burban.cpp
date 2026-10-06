 /*Епік 1. Algotester task: "Interesting Game" . Бурбан Данило, ШІ-14*/
 #include <iostream>

 using namespace std;
 int main(){
    int N;
    int M;
    cin>>N>>M;
    if(N>=1 && N<=100 && M>=1 && M<=100)
    if((N*M)%2==0){
        cout<<"Dragon";
        return 0;
    }
    else{
        cout<<"Imp";
        return 0;
    };
 }