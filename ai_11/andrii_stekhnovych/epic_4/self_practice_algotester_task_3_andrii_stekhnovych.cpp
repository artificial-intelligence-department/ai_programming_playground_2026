#include <iostream>
#include <cmath>

using namespace std;
int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    string answer="";
    int sqrt_t=sqrt(n);
    for (int i = 0; i<(sqrt_t); i++) {
        int left=0;
        int right=i;
        while(right>-1) {
            answer+=s[sqrt_t*left+right];
            left++;
            right--;
        }
        
    }  
    for (int i = 1; i<sqrt_t; i++) {
        int left=i;
        int right=sqrt_t-1;
        while(left<sqrt_t) {
            answer+=s[sqrt_t*left+right];
            left++;
            right--;
        }
        
    }
    cout << answer;

}