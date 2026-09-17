#include <iostream>
using namespace std;

int main(){
    int m; 
    int n;
    cin >> m;
    cin >> n;
    if (((m * n) % 2) == 1){
        cout << "Imp" << endl;
    }
    else{
        cout << "Dragon" << endl;
    }
}