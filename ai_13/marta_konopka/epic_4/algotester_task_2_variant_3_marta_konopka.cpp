// variant 3 
#include <iostream>
using namespace std;

const int MAX_N = 1000;

int main(){
    int n;
    if(!(cin >> n)){
        return 0;
    }
    int a[MAX_N];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int position1 = 0;
    int position2 = n - 1;

    while(true){
    
    if(position1 == position2){
        cout << position1 + 1 << " " << position2 + 1 << endl;
        cout << "Collision" << endl;
        break;
    }
    if(position1 + 1 == position2){
    cout << position1 + 1 << " " << position2 + 1 << endl;
    cout << "Stopped" << endl;
    break;
    }
    if(position1 > position2){
        cout << position1 + 1 << " " << position2 + 1 << endl;
        cout << "Miss" << endl;
        break;
        
    }
    int step1 = a[position1];
    int step2 = a[position2];

    position1 += step1;
    position2 -= step2;
}

    return 0;
}