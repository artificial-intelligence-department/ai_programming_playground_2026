#include <iostream>
#include <cmath>
using namespace std;

double const e = 0.0001;

int main(){

    double a = 0.1;
    double sum = a;

    for(int i = 2; a >= e; i++){
        a *= (i - 1) / 10.0;
        sum += a;
        if(a < e){
            break;
        }  
    }

    cout << "Sum: " << sum << endl; 
    
    return 0;
}