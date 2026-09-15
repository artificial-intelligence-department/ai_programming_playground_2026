#include <iostream>

using namespace std;
int main(){
    int n = 0, div = 0;
    cin>>n;
    int votes[n];
    long places = 0;
    for( int n_temp = 0; n_temp < n; n_temp++){
        cin>>votes[n_temp];
        places += votes[n_temp];
        if(n_temp == 0){
            div = votes[n_temp];
        }
        else{
            div = gcd(votes[n_temp], div);      
        }
    }
    cout<< places/div;

}
