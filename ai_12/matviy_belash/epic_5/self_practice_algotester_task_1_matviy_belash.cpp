/*
Белаш Матвій ШІ-12
Завдання з алготестеру "Снігурочка"
*/
#include <iostream>
#include <string>

using namespace std;

int main() {

    int n, m;
    string s;
    cin >> n >> m >> s;

    for (int i = 0; i < m; i++){

        char dia;
        cin >> dia;

        if(dia == 'i') {
            int p;
            char c;
            cin >> p >> c;
            s.insert(p, 1, c);
        }else if(dia == 'd'){
            int p;
            cin >> p;
            s.erase(p - 1, 1);
        }else if(dia == 'q'){
            int a, b;
            cin >> a >> b;
            a--; 
            b--;
            int len = 0;
            while(a + len < s.length() && b + len < s.length() && s[a + len] == s[b + len]) {
                len++;
            }
            cout << len << endl;
        }
    }

    return 0;
}