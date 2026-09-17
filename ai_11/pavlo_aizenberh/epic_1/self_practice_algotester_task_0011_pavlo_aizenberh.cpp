#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    long long answer = 0;
    int packs;
    cin >> packs;
    
    for (int i = 0; i < packs; i++){
        int a; 
        cin >> a;

        answer += max(0, a - 1);
    }
    cout << answer << endl;
    return 0;
}