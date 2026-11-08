/*Epic 5 - Снігурочка
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(string w) {
    for (int k = 0; k <(int)w.size(); k++) {
        w[k] = tolower(w[k]);
    }
    
    int i = 0;
    int j = (int)w.size() - 1;
    while (i < j) {
        if (w[i] != w[j]) {
            return false;
        }
    i++;
    j--;
    }
    return true;
}

int main() {
    string w;
    int count = 0;
    while (cin >> w){
        if (isPalindrome(w)) {
            count++;
        }
    }
    cout << count;
    return 0;
}