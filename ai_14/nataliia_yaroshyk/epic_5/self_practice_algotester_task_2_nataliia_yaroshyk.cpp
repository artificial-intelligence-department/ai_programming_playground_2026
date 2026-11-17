// Щасливий результат
#include <iostream>
#include <string>
using namespace std;

int main(){
    string x;
    cin >> x;
    int cnt = 0;
    for(int i = 0; i < x.length(); i++){
        if(x[i] == '4' || x[i] == '7'){
            cnt++;
        }
    }
    cout << cnt;
    return 0;
}