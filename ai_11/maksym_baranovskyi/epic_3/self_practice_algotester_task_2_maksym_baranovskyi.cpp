//Скільки заплатити?

#include <iostream> 

using namespace std;

int main(){
    
    int x, y;
    cin >> x >> y;
    
    if(x<y){
        if(x+1 != y){
            cout << x+1;
        }
        else{
            cout << -1;
        }
    }
    else {
        if(y+1 != x){
            cout << y+1;
        }
        else{
            cout << -1;
        }
    }
    
    
    
    return 0;
}
