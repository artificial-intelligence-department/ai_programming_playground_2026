// variant 1 
#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    if(!(cin >> n)){
        return 0;
    }
        int total = 0;
        string word;
        getline(cin, word);

        for (int r = 0; r < n; r++){
            string line;
            getline(cin, line);

            for(int i = 0; i < line.length(); i++){
                if(line[i] == '#'){
                    if(i == 0 || (line[i - 1] != '#')){
                        total++;
                    }
                }
            }

        }
        cout << total;
        return 0;

}
