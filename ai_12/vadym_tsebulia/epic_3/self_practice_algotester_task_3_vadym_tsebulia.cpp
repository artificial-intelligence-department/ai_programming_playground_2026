// Коля, Вася і Теніс
#include <iostream>
#include <string>
using namespace std;

int main(){
        int n;
        string matches;
        cin >> n;
        cin >> matches;
        int k = 0, v = 0;
        int setsK = 0; int setsV = 0;
        for (int i = 0; i < n; i++){
                
                if (matches[i] == 'K') k++;
                else v++;
                

                if (k >= 11 && k - v >= 2){
                setsK++;
                k = 0;
                v = 0;
                }

                if (v >= 11 && v - k >= 2){
                setsV++;
                v = 0;
                k = 0;
                }
        }
        cout  << setsK << ":" << setsV << endl;
        if (k > 0 || v > 0)
        cout << k << ":" << v << endl;

        return 0;
}
