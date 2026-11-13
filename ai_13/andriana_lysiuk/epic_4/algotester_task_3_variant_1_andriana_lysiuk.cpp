/*
Algotester lab 3
Лисюк Андріана
ШІ-13
Варіант 1
*/

#include <iostream>
#include <string>

using namespace std;

int main(){
    int N;
    cin >> N;
    cin.ignore();
    int rituals = 0;
    for(int i = 0; i < N; i++){
        string s;
        getline(cin, s);
        bool in_ritual = false;
        for(int j = 0; j < s.length(); j++){
            if (s[j] == '#'){
                if(in_ritual == false){
                    rituals++;
                    in_ritual = true;
                }
            } else {
                    in_ritual = false;
                }
            }
        }
    cout << rituals;
    return 0;
}