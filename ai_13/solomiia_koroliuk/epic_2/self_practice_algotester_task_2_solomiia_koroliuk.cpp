
/* Task 2001: Is it autumn yet? */

#include <iostream>

using namespace std; 

int main(){
    
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++){
        
        int m;
        cin >> m;
        
        switch(m){
            
            case 9:
            case 10:
            case 11:
            
                cout << "yes" << endl;
                break;
            
            default:
                cout << "no" << endl;
                break;
        }
    }
    
    return 0;
}
