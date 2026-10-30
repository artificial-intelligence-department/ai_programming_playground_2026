#include <iostream>
#include <string>
using namespace std;
int main(){
    string word;
    int count = 0;
    cin >> word;
    count = word.length();
    int countl = 1;
    string s;
    bool fact = false;
    for(int i = 0; i < count; i++){
         if(count != 0 && i == count - 1){
            fact = true;
        }
        if(fact == true){
            if(countl > 1){
             cout << word[i] << countl;
            }
            else{
                cout << word[i];
            }
             fact = false;
             break;
        }
       
        if(word[i] == word[i + 1]){
            countl++;
            continue;
        }
        if(word[i] != word[i + 1]){
            if(countl > 1){
        cout<< word[i] << countl;
    }
        else{
            cout<< word[i];
        }
        countl = 1;
        continue;
    }
    
}
return 0;
}
