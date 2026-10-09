#include <iostream>

using namespace std;

int main(){
    long long d1,d2,d3,d4,d5;
    
    cin >> d1;
    cin >> d2;
    cin >> d3;
    cin >> d4;
    cin >> d5;

    if(d1 <= 0){
        cout << "ERROR";
    }
    else if(d2 <= 0){
        cout << "ERROR";
    }
    else if(d1 < d2){
        cout << "LOSS";
    }
    else if(d3 <= 0){
        cout << "ERROR";
    }
    else if(d2 < d3){
        cout << "LOSS";
    }
    else if(d4 <= 0){
        cout << "ERROR";
    }
    else if(d3 < d4){
        cout << "LOSS";
    }
    else if(d5 <= 0){
        cout << "ERROR";
    }
    else if(d4 < d5){
        cout << "LOSS";
    }
    else{
        cout << "WIN";
    }

    return 0;
}

