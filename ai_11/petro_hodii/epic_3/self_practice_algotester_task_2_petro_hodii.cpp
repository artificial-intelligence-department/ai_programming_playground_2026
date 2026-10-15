#include <iostream>
#include <string>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string str;
    int V_score = 0;
    int K_score = 0;
    int V_win = 0;
    int K_win = 0;

    cin >> n >> str;

    for(int i = 0; i < n; i++){
        if(str[i] == 'V'){V_score++;}
        else{K_score++;}

        if(V_score >= 11 && (V_score - K_score) >= 2){
            V_win++;
            V_score=0;
            K_score=0;
        }
        else if(K_score >= 11 && (K_score - V_score) >= 2){
            K_win++;
            V_score=0;
            K_score=0;
        }
    }

    cout << K_win << ":" << V_win << endl;
    if(V_score != 0 || K_score != 0){
        cout << K_score << ":" << V_score;
    }


    return 0;
}