#include <iostream>

using namespace std;
int main(){
    int n_of_votes = 0, div = 0;// n of places of party = votes for party/gcd of all votes
    cin>>n_of_votes;
    int votes[n_of_votes];
    long all_votes = 0;
    for( int n_of_votes_temp = 0; n_of_votes_temp < n_of_votes; n_of_votes_temp++){
        cin>>votes[n_of_votes_temp];
        all_votes += votes[n_of_votes_temp];
        if(n_of_votes_temp == 0){
            div = votes[n_of_votes_temp];
        }
        else{
            div = gcd(votes[n_of_votes_temp], div);// if votes_1 % div == 0 && div % div_1 == 0 => votes_1 % div_1 == 0 , div_1 - common divisor
        }
    }
    cout<< all_votes/div;

}
