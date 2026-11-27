/* 
Задача: Лабораторна робота Algotester №6
Варіант: №1
Автор: Вероніка Третяк
Група: ШІ-13
*/
#include <iostream>
using namespace std;
static int nextnode[1000001][26];
static int frequency[1000001];

int main(){
int n, k;
if(!(cin >> n >> k)){
    return 0;
}
int lastnode = 0;
bool letters[26] = {};
int lettercount = 0;
for(int i = 0; i < n; i++){
    char word[11];
    if(!(cin >> word)){
        return 0;
    }
    int node = 0;
    for(int j = 0; word[j] != '\0'; j++){
        char c = word[j];
        if(c >= 'A' && c <= 'Z'){
            word[j] = 'a' + (c - 'A');
        }
        int index = word[j] - 'a';
        if(nextnode[node][index] == 0){
            lastnode++;
            nextnode[node][index] = lastnode;
        }
        node = nextnode[node][index];
    }
    frequency[node]++;
    if(frequency[node] == k){
        for(int j = 0; word[j] != '\0'; j++){
            int index = word[j] - 'a';
            if(!letters[index]){
                letters[index] = true;
                lettercount++;
            }
        }
    }
}
if(lettercount == 0){
    cout << "Empty!\n";
    return 0;
}
cout << lettercount << '\n';
int print = 0;
for(int j = 25; j >= 0; j--){
    if(letters[j] ){
        if(print > 0){
            cout << ' ';
        }
        cout << char('a' + j);
        print++;
}
}
cout << '\n';
return 0;
}