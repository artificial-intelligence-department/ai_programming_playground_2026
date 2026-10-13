/* Task 0281: Поле чудес */

#include <iostream>
#include <string>

using namespace std;

int main(){
    
    string s;
    cin >> s;
    
    int c = 0;
    
    
    for (int i = 0; i < s.length(); i++){
        bool is_first_time = true;
        
        for (int j = 0; j < i; j++){
            if (s[i] == s[j]){
                is_first_time = false;
                break;
            }
        }
        
        if (is_first_time){
            c+=1;
        }
    }
    
    cout << c << endl;
    
    return 0;
}

