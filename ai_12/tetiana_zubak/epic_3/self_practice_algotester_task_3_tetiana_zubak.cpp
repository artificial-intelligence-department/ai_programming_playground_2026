#include <iostream>
#include <string>

using namespace std;

int way(int n, int sixseven){
    if(sixseven == 0 || sixseven == n) return 1;
    return way(n - 1, sixseven - 1) + way(n - 1, sixseven);
}

int main(){
    string sf;
    cin >> sf;
    int n = sf.length();
    int sixseven = 0;
    for(int i = 0; i < n; i++){
        if(sf[i] == '7') sixseven++;
    }
    cout << way(n, sixseven);

    return 0;
}