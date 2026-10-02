/*Epic 2 -
Коля, Вася і Теніс
Ші - 14*/
#include <iostream>
using namespace std;

int main(){
    int n;
    int K_score=0;
    int V_score=0;
    int K_win=0;
    int V_win=0;
    cin>>n;
    for (int i = 0;i<n;i++){


        char x;
        cin>>x;
        if(x == 'K'){
            K_score++;
        }else if(x == 'V'){
            V_score++;
        }

        if((K_score>=11||V_score>=11) &&(K_score-V_score>=2)){
            K_win++;
            K_score=0;
            V_score=0;
        }else if((K_score>=11||V_score>=11) &&(V_score-K_score>=2)){
            V_win++;
            K_score=0;
            V_score=0;
        }


    }
        cout<<K_win<<":"<<V_win<<endl;
        if(K_score!=0 || V_score!=0){
        cout<<K_score<<":"<<V_score;
        }
    return 0;
}