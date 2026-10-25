#include <iostream>
#include<string>
using namespace std;

int main(){

    string input = "";
    cin >> input;

    char prev = input[0];
    cout << prev;
    char curr = prev;

    int count = 1;
    for(int i = 1; i < input.length(); i++ ){

        prev = curr;
        curr = input[i];

        if(curr == prev){
            count ++;
        continue;
        }

        if(count > 1){
            cout << count;  
            count = 1;
        }

        cout << curr;
    }
    
    if(count > 1){
    cout << count;  
    }
}
