#include <iostream>
using namespace std;

int main(){
    int N=0;
    cin>>N;
    N++;
    string M[N];
    for(int i=0;i<N;i++){
        getline(cin,M[i]);
    }
    int todo=0;
    for(int i=0; i<N;i++){
        bool isNewSpell=true;
        int n=M[i].length();
        for(int ii=0;ii<n;ii++){
            if(M[i][ii]=='#'){
                if(isNewSpell==true){
                    todo++;
                    isNewSpell=false;
                }
            }
            else{
                isNewSpell=true;
            }
        }
    }
    cout<<todo;
    return 0;
}