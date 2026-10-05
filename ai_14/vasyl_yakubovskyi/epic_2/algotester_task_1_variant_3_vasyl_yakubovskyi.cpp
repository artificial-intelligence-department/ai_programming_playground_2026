/*
Task from algotester option 3
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>
using namespace std;

int main() {

    
    long long cub_c, cub_p = 0;
    cin >> cub_p;

      if(cub_p <= 0) {
        cout << "ERROR" ; return 0;
    }

    for (int i = 1; i<5; i++){

        cin >> cub_c;
        if(cub_p < cub_c){
             cout << "LOSS" ; return 0;
        }
        if(cub_c <= 0){
             cout << "ERROR" ; return 0;
        }

        cub_p = cub_c;
        
    }
    
    

    cout << "WIN";

    return 0;
}