    // щасливі рядки
    #include <iostream>
    #include <string>
    using namespace std;

    int main(){
        string t = "";
        string s = "";
        long long sFour = 0;
        long long sSeven = 0;
        long long tFour = 0;
        long long tSeven = 0;
        long long sLen = 0;
        long long tLen = 0;
        cin >> sLen >> tLen >> s >> t;
        long long max = (sLen>tLen)? sLen : tLen;
        for(int i = 0; i < max; i++){
            if(i < sLen){
                if(s[i] == '4') sFour ++;
                else if(s[i] == '7') sSeven ++;
            }
            if(i < tLen){
                if(t[i] == '4') tFour++;
                else if(t[i] == '7') tSeven ++;
            }
        }
        long long res = (sLen + 1)*(tLen + 1) - 1 - tFour*sFour - sSeven*tSeven;
        cout << res << "\n";
    }