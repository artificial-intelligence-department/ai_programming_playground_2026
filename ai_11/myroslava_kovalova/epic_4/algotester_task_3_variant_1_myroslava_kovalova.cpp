#include <iostream>
#include <string>

using namespace std;
int main(){
    string spell[1000];
    int N =0;
    cin>>N;
    cin.ignore();
    
    for (int i =0; i<N;i++){
        getline(cin, spell[i]);
    }
    int count = 0;

    for (int i =0; i<N ;i++){
        if(spell[i][0]=='#'){
            count++;
        }
    }

    for (int i =0; i<N ;i++){
        for (int j = 1; j<spell[i].length(); j++){
            if(spell[i][j]=='#' && spell[i][j-1]!='#'){
                count++;
            }
        }
    }
    cout<<count;

}