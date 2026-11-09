#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N,K;
    cin>>N>>K;

    string *words=new string[N];

    for(int i=0;i<N;i++){
        cin>>words[i];

        for(int j=0;j<words[i].length();j++){
            if(words[i][j]-91<0){
                words[i][j]+=32;
            }
        }
    }

    sort(words,words+N);

    bool Is[26]{};

    int i=0;

    while(i<N){
        int count=1;

        int j=i+1;

        while(j<N && words[i]==words[j]){
            count++;
            j++;
        }

        if(count>=K){
            for(int c=0;c<words[i].length();c++){
                Is[words[i][c]-'a']=true;
            }
        }

        i=j;
    }

    int M=0;

    for(int i=25;i>=0;i--){
        if(Is[i]){
            M++;
        }
    }

    if(M==0){
        cout<<"Empty!";
    }
    else{
        cout<<M<<endl;

        for(int i=25;i>=0;i--){
            if(Is[i]){
                cout<<(char)(i+'a')<<" ";
            }
        }
    }

    delete[] words;
    return 0;
}