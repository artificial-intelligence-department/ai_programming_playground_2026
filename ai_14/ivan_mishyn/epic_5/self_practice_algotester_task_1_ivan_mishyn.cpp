#include <iostream>
using namespace std;

int main(){
    string t,s;
    cin>>t>>s;
    int tLen=t.length();
    int sLen=s.length();
    bool isS[26]{};
    int count[26]{};
    long long koef=0;
    int** letters = new int*[26];

    for(int i = 0; i < 26; i++){
     letters[i] = new int[tLen];
    }

    for(int i = 0; i < sLen; i++){
        isS[s[i]-'a'] = true;
    }

    for(int i = 0; i < tLen; i++){
        int x = t[i]-'a';
        if(!isS[x]) continue;
        letters[x][count[x]] = i;
        count[x]++;
    }
    for(int i=0;i<sLen;i++){
        int x=s[i]-'a';
        for(int j=0; j<count[x]; j++){
            if(letters[x][j]<=tLen-sLen+i && letters[x][j]>=i) koef += i+1;
            if(letters[x][j]>tLen-sLen+i) break;
        }
        
    }

    for(int i=0; i<26; i++){
        delete[] letters[i];
    }
    delete[] letters;
    cout<<koef;
    return 0;
}
