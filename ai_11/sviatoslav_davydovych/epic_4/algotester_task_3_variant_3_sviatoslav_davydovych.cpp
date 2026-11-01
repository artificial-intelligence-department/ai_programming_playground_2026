/* 
Lab 3v3
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <string>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    cin >> line;

    int c = 0;
    char last;
    for (char i : line){
        if (c==0) {
            last = i;
            c++;
            continue;
        }
        if (i!=last){
            if (c==1) cout << last;
            else cout << last << c;
            c = 0;
        }
        last = i;
        c++;
    }
    if (c==1) cout << last;
    else cout << last << c;
}