/*Дужкова інверсія. 
*/
#include <iostream>
#include <string>

using namespace std;

int main(){
    string s;
    cin >> s;
    int n = s.length();

    if(n % 2 == 1){
        cout << "impossible" << endl;
        return 0;
    }
    int p[5002];
    p[0] = 0;
    for(int i = 1; i <= n; i++){
        if(s[i - 1] == '('){
            p[i] = p[i - 1] + 1;
        }
        else{
            p[i] = p[i - 1] - 1;
        }
    }
    bool correct = true;
    for(int i = 0; i <= n; i++){
        if(p[i] < 0){
            correct = false;
        }
    }
    if(correct && p[n] == 0){
        cout << "possible" << endl;
        return 0;
    }

    int sufMin[5003];
    sufMin[n + 1] = 1000000;
    for(int i = n; i >= 0; i--){
        sufMin[i] = p[i];
        if(sufMin[i + 1] < sufMin[i]){
            sufMin[i] = sufMin[i + 1];
        }
    }

    bool ok = false;
    for(int l = 1; l <= n && !ok; l++){
        if(p[l - 1] < 0){
            break;
        }
        int inMax = -1000000;
        for(int r = l; r <= n; r++){
            if(p[r] > inMax){
                inMax = p[r];
            }
            if(inMax > 2 * p[l - 1]){
                break;
            }
            int d = p[r] - p[l - 1];
            if(p[n] == 2 * d && sufMin[r + 1] >= 2 * d){
                ok = true;
                break;
            }
        }
    }
    if(ok){
        cout << "possible" << endl;
    }
    else{
        cout << "impossible" << endl;
    }

    return 0;
}