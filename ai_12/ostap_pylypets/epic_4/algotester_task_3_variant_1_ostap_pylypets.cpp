/*лабораторна робота з алготестеру #3 v1*/
#include <iostream>
#include <string>
using namespace std;
int main(){
    int n, res=0;
    string str;
    cin >> n;
    cin.ignore();
    for(int i = 0; i< n; i++){
        getline(cin, str);
        for(int j = 0; j < str.length(); j++){
            if(str[j] == '#' && (j == 0 || str[j-1] != '#')){
            res++;
            }
        }
    }
    cout << res;
    return 0;
}