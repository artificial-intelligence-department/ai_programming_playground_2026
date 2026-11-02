#include <iostream>
#include <string>
using namespace std;

int n_o_c(int n, int number, int m){
    for(int i = 1; i<=(number-m); i++){
        n /= 10;
    }
    n = n%10;
    return n;
}


int main(){

    string s;
    cin >> s;
    int length_copy = s.length();
    char s_copy[s.length()];

    int n = 0;
    int k = 0;
    int t = 0;
    int number_of_n = 0;
    int number_of_char = 0;
    for(int i =0; i < s.length(); i++){
        if(s[i] == s[i+1]){
            int j = i;
            while(s[j] == s[i]){
                n++;
                j++;
            }
            t = n;
            while(t != 0){
                number_of_n++;
                t /= 10;
            }
            s_copy[k] = s[i];
            for(int m =1; m <=number_of_n; m++){
                s_copy[k+m] = n_o_c(n, number_of_n, m) + '0';
            }
            length_copy -= n-(1+number_of_n);
            i += n-1;
            n = 0;  
            k+= 1+number_of_n;
            number_of_n = 0;
        }else{
            s_copy[k] = s[i];
            k++;   
        }
    }

    for(int i =0; i < length_copy; i++){
        cout << s_copy[i]; 
    }

    return 0;
}