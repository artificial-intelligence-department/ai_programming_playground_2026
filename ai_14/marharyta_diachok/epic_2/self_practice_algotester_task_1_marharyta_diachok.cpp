/* 
Задача: Algotester Self-Practice №1.
Автор: Дячок Маргарита.
Група: ШІ-14
*/
#include <iostream>
#include <string>
using namespace std;
int main () {
string S[1000] = {""};
int W[1000] = {0};
int N = 0;
cin >> N;
for (int i = 0; i < N; i++) {
    cin >> S[i] >> W[i];
}
int max[1000] = {0};
int sum = 0;
for (int i = 0; i < N; i++) {
    if (S[i] == "") {continue;}
    max[i] = W[i];
    for (int j = 0; j < N; j++) {
        if (S[i] == S[j]) {
            if (max[i] < W[j]) {
                max[i] = W[j]; }
            if (j != i) {S[j] = "";}
        } 

    }

}
for (int i = 0; i < N; i++) {
sum += max[i];}
cout << sum << endl;

    return 0;
}