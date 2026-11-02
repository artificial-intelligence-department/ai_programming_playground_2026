/*
Белаш Матвій ШІ-12
Завдання з алготестеру "Допоможе чи заб'є?"
*/
#include <iostream>
#include <string>
using namespace std;

int main(){

    int k = 0;
    cin >> k;

    string s; 
    cin >> s;

    int a = 0;
    int size = s.length();

    for(int i = 0; i < size; i++){
        if(size - i < 6){
            break;
        }
        if(s[i] == 'T'){
            if(s[i+1] == 'O'){
                if(s[i+2] == 'I'){
                    if(s[i+3] == 'L'){
                        if(s[i+4] == 'E'){
                            if(s[i+5] == 'T'){
                                a ++;
                                i += 5;
                            } 
                        } 
                    } 
                }           
            }
        }
    }

    if(a >= k) cout << "YES";
    else cout << "NO";
        
    return 0;
}


