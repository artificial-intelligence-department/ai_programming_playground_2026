#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int main(){
    int N = 0;
    cin >> N;
    int K = 0;
    cin >> K;
    int count[26] = {0};
    string some[1000004];
    for(int i = 0; i < N; i++){
        cin >> some[i];
        int kilk = some[i].length();
        for(int j = 0; j < kilk; j++){
                if(some[i][j] >= 'A' && some[i][j] <= 'Z'){
                    some[i][j] = some[i][j] + 32;
                }

            }   
    }
    sort(some, some + N);
    int povtor = 0;
    for(int i = 0; i < N; i++){
        if(i > 0 && some[i] == some[i - 1]){
            povtor++;      
        }
        else{
            povtor = 1;    
        }

        if(povtor == K){  
            for(int p = 0; p < some[i].length(); p++){
                count[some[i][p] - 'a'] = 1;
            }
        }
    }
    

int rah = 0;
int buk[26];
for(int f = 'z' - 'a'; f >= 0; f--){
    if(count[f] >= 1){
        buk[rah] = 'a' + f;
        rah++;
    }
}
if(rah == 0){
    cout << "Empty!\n";
    return 0;
}
cout << rah << "\n";
for(int x = 0; x < rah; x++){
    char letter = (char)buk[x];
        cout << letter << " ";
}
return 0;
}
