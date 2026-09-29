/* Algotester
   Поле чудес
   Ярошик Наталія
   ШІ-14 */
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    int n = 0;
    cin >> s;
    for(int i=0; i<= s.length(); i++){
        if(s.find(s[i]) == i){
            n += 1;
        }
    }
    cout << n;
    return 0;
}