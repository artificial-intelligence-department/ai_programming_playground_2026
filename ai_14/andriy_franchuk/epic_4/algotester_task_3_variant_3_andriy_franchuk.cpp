#include <iostream>

using namespace std;

int main() {
    char S[100000] = {0};
    cin >> S;

    char prev = S[0];
    int counter = 0;
    for(char s_1 : S) {
        if(s_1 != prev){
            if(counter > 1){
                cout << prev << counter;
            }else{
                cout << prev;
            }

            counter = 0;
        }
        
        counter++;
        prev = s_1;
    }
    cout << endl;

    return 0;
}