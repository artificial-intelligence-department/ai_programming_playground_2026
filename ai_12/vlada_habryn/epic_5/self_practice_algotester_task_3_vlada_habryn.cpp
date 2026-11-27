#include <iostream>
#include <string>
using namespace std;
int main() {
    int n;
    char c;
    cin >> n >> c;
    string best;
    for (int i = 0; i<n;i++){
        string s;
        cin>>s;
        int position = s.length();
        for(int j = 0; j < s.length();j++){
            if (s[j]>c){
                position = j;
                break;
            }
        }
        s.insert(position, 1, c);
        if (i==0 || s < best){
            best = s;
        }
    }
    cout<<best;


    return 0;
}
