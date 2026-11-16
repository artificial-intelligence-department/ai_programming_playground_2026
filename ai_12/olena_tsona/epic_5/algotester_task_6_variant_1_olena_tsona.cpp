#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string words[100000];
string tmp[100000];    


void myMerge(int l, int m, int r, bool ascending) {
    int n1 = m - l + 1;
    int n2 = r - m;

    
    for (int i = 0; i < n1; i++) {
        tmp[l + i] = words[l + i];
    }
    for (int j = 0; j < n2; j++) {
        tmp[m + 1 + j] = words[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        bool condition;
        if (ascending) {
            condition = (tmp[l + i] <= tmp[m + 1 + j]); 
        } else {
            condition = (tmp[l + i] >= tmp[m + 1 + j]); 
        }

        if (condition) {
            words[k++] = tmp[l + i++];
        } else {
            words[k++] = tmp[m + 1 + j++];
        }
    }

    
    while (i < n1) words[k++] = tmp[l + i++];
    while (j < n2) words[k++] = tmp[m + 1 + j++];
}


void mySort(int l, int r, bool ascending) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mySort(l, m, ascending);
        mySort(m + 1, r, ascending);
        myMerge(l, m, r, ascending);
    }
}

int main(){
   

    int N = 0, K = 0;
    if (!(cin >> N >> K)) return 0;

    
    for (int i = 0; i < N; i++){
        cin >> words[i];
        for (int j = 0; j < words[i].size(); j++){
            words[i][j] = tolower(words[i][j]);
        }
    }

    
    if (N > 0) {
        mySort(0, N - 1, true);
    }

    bool used[26] = {false};




    int i = 0;
    while (i < N){
        int j = i;
        while (j < N && words[j] == words[i]){
            j++;
        }
        
        
        if (j - i >= K){
            for (int p = 0; p < words[i].size(); p++){
                used[words[i][p] - 'a'] = true;
            }
        }
        i = j;
    }

    
    int M = 0;
    for (int c = 0; c < 26; c++){
        if (used[c]) {
            M++;
        }
    }

    if (M == 0){
        cout << "Empty!\n";
        return 0;
    }

    cout << M << "\n";
    bool first = true;
    for (int c = 25; c >= 0; c--){
        if (used[c]) {
            cout << (first ? "" : " ") << char('a' + c);
            first = false;
        }
    }
    cout << "\n";

    return 0;
}