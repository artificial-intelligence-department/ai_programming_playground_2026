#include <iostream>
#include <string>
using namespace std;

int main(){
    string str;
    cin >> str;
    int N = str.length();
    if (N == 1){
        cout << str[0];
        return 0;
    }
    int count = 1;
    for (int i = 0; i < N; i++){
        if (str[i] == str[i + 1]){
            count++;
            continue;
        }
        else{
            cout << str[i];
            if (count > 1) cout << count;
            count = 1;
        }
    }
}