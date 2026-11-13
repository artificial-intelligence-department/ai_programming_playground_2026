#include <iostream>
#include<string>

using namespace std;

bool check(string s1, string s2, int n) {
    return s1.compare(n, s2.size(), s2) == 0;
}

int main(){
    int n;
    cin >> n;
    string s1[n];
    string s2[n];

    for(int i = 0; i < n; i++){
        cin >> s1[i] >> s2[i];
    }

    for(int i = 0; i < n; i++){
        int s1_size = s1[i].size();
        int s2_size = s2[i].size();
        int k = s1_size-s2_size;
        if(k==0){
            if(s1[i]==s2[i]){
                cout << "Sergei" << endl;
                continue;
            }else{
                cout << "Larry" << endl;
                continue;
            }
        }

        if(k%2==1){
            if(check(s1[i], s2[i], k/2)&&check(s1[i], s2[i], k/2+1)){
                cout << "Sergei" << endl;
                continue;
            }else{
                cout << "Larry" << endl;
                continue;
            }
        }else{
            if(check(s1[i], s2[i], k/2)||(check(s1[i], s2[i], k/2 - 1)&&check(s1[i], s2[i], k/2 + 1))){
                cout << "Sergei" << endl;
                continue;
            }else{
                cout << "Larry" << endl;
                continue;
            }
        }
    }
}