#include <iostream>
#include <string>

using namespace std;

int main(){
    int n;
    cin >> n;
    int bal = 0;

    for(int i = 0; i < n; i++){
        string es;
        int m;
        cin >> es >> m;

        if(es == "earn"){
            bal += m;
        }
        if(es == "spend"){
            bal -= m;
        }
        if(bal < 0){
            cout << "debt";
            return 0;
    }
    }
    cout << "chinazes";

    return 0;
} 