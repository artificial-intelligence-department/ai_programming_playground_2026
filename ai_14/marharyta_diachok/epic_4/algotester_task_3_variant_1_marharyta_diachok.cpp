/* 
Задача: Algotester Lab3 v1.
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
#include <string>
using namespace std;
int main() {
int N;
cin >> N;
if(N < 1 || N > 1000) return 0;
cin.ignore();
string* rows = new string[N];
int cencored = 0;
for(int i = 0; i < N; i++) {
getline(cin, rows[i]);
 int word_count = 0;
 for (int j = 0; j < rows[i].length(); j++) {
 if (rows[i][j] != ' ') {
    if (j == 0 || rows[i][j - 1] == ' ') {
        word_count++;}}}
        
    if (word_count > 42) {
        delete[] rows;
        return 0;}}

for(int i = 0; i < N; i++) {
    string text = rows[i];
    char blurred = '#';
    for(int j = 0; j < text.length(); j++) {
    if(text[j] == blurred) {
        if(j == 0 || text[j - 1] != blurred) { cencored++;}} 
}}
cout << endl;
cout << cencored;
delete[] rows;
    return 0;
}

