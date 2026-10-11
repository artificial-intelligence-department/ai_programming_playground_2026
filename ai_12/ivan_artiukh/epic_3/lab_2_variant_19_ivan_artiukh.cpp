#include <iostream>
using namespace std;

int main(){

int n = 2;
double limit_of_precision = 0.0001;
double a_n = (double)n / ( (n-1) * (n-1) );
double sum = a_n;
while(true){
    a_n *=(double)(n+1)*(n-1)*(n-1)/(n*n*n);

    if( a_n >= limit_of_precision){
        sum += a_n;
    }

    else{
        break;
    }
    n++;
}

cout<<  "Сума ряду: " << sum << endl;

}