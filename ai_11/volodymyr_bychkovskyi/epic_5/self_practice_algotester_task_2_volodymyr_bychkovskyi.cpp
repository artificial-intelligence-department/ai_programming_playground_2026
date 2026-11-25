/*
Назва: Найкращий акумулятор
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    cin >> n;
    char c;
    cin >> c;
    string best = "";
    bool is = true;
    for(int i=0; i<n; i++){
        string word ="";
        cin >> word;
        int len = word.size();
        for(int j=0; j<word.size(); j++){
            if (word[j]>c){
                word.insert(j, 1, c);
                break;
            }
            
        }
        if (len == word.size()) {
            word += c;
        }
        
        if(is){
            best = word;
            is = false;
            continue;
        }
        else{
            if(word<best){
            best = word;
            }
        }
            
    }
    cout << best;
}