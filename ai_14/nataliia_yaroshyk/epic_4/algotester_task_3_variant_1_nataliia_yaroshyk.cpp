/*  Algotester lab 3v1
    Ярошик Наталія
    ШІ-14 */
#include <iostream>
#include <string>
using namespace std;

int main(){
    int N;
    int count = 0;
    string w;
    cin >> N;
    while(getline(cin, w)){
        for(int i = 0; i < w.length(); i++){
                if(w[i] == '#'){
                    if(i == 0 || w[i - 1] != '#') count++;
                }
        }
    }

    cout << count;
    return 0;
}