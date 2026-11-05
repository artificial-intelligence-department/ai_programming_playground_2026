#include <iostream>
#include <string>
using namespace std;

/*
 * Задача: Algotester Lab 3v1
 * Щербак Орислав
 * Група ШІ-11
 */

int main(){
    int n;
    cin >> n;
    if(n < 1 || n > 1000){
        return 0;
    }
    string line;
    getline(cin, line);
    int rituals = 0;
    for(int i = 0; i < n; i++){
        getline(cin, line);
        int length = line.length();
        for(int j = 0; j < length; j++){
            if(line[j] == '#'){
                if(j == 0 || line[j-1] != '#'){
                    rituals++;
                }
            }
        }
    }
    cout << rituals << endl;
}