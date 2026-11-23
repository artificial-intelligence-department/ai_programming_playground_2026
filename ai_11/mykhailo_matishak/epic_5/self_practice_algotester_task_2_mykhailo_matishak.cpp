/*Сет
*/
#include <iostream>
#include <string>

using namespace std;

int main(){
    int n;
    cin >> n;

    int a[10000][4];
    int code[10000];
    int rest[81] = {0};
    string colors = "RGB";
    string textures = "FPE";
    string shapes = "DSO";
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        a[i][0] = s[0] - '1';
        a[i][1] = colors.find(s[1]);
        a[i][2] = textures.find(s[2]);
        a[i][3] = shapes.find(s[3]);
        code[i] = a[i][0] * 27 + a[i][1] * 9 + a[i][2] * 3 + a[i][3];
        rest[code[i]]++;
    }
    long long ans = 0;
    for(int j = 0; j < n; j++){
        rest[code[j]]--;
        for(int i = 0; i < j; i++){
            int t = 0;
            for(int k = 0; k < 4; k++){
                int z = (6 - a[i][k] - a[j][k]) % 3;
                t = t * 3 + z;
            }
            ans = ans + rest[t];
        }
    }
    cout << ans << endl;

    return 0;
}