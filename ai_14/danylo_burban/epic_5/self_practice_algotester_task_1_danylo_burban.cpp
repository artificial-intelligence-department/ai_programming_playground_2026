/*Epic 5 - Снігурочка
Данило Бурбан
Ші - 14*/

#include <iostream>
#include <string>
using namespace std;

int main(){
    bool check=true;
    int count =0;
    string word;
    while(cin>>word){
        if(word.empty()){
            break;
        }
        check=true;
        for(int i=0; i<word.length();i++){
            word[i]=tolower(word[i]);
        }
        for(int i=0; i<word.length()/2;i++){
            if(word[i]!=word[word.length()-i-1]){
                check =false;
            }
        }
        if(check){
            count ++;
        }
        
    }
    cout<<count;
}