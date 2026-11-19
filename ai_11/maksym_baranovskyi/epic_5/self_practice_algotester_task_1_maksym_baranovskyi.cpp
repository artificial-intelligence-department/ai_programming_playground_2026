//Андрійко та рядки
#include <iostream>
using namespace std; 

int main(){
    int n, k;
    cin >> n >> k;

    string res;

    if(k > n || (k == 1 && n > 1)){
        cout << -1;
        return 0;
    }

    if(k == 1){
        cout << 'a';
        return 0;
    }

    int p = n - (k - 2);
    for(int i = 0; i < p; i++){
        if(i % 2 == 0){
            res += 'a';
        }
        else{
            res += 'b';
        }
    }
    for(int j = 0; j < k - 2; j++){
        res += char('c' + j);
    }

    cout << res;

    return 0;
}