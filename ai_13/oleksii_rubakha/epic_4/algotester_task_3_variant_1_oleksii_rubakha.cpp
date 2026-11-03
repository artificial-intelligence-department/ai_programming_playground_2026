#include <iostream>
#include <string>

using namespace std;

int main(){

    int n;
    cin >> n; cin.ignore();
    int count = 0;

    for (int i = 0; i < n; i++){

        string s;
        getline(cin, s);

        bool inGroup = false;

        for (int j = 0; j < s.length(); j++){

            if (s[j] == '#'){
                if (!inGroup){
                    count++;
                    inGroup = true;
                }
            }else{
                inGroup = false;
            }
        }
    }

    cout << count;

    return 0;
}