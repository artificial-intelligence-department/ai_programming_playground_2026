/* Task 1555 - Burdochvirus Vaccine */

#include <iostream>
#include <string>

using namespace std;

int main(){
    
    string s, t;
    cin >> s >> t;
    
    int n = s.length();
    
    cout << n << endl;
    
    for (int i = 0; i < n; i++){
        
        char needed_letter = t[i]; //визначаємо потрібну літеру
        int pos = s.find(needed_letter); //шукаємо її входження
        
        cout << pos + 1;
        if (i + 1 < n) cout << ' ';
        
        
        // видаляємо символ із поточної позиції pos і додаємо в кінець рядка s        
        s.erase(pos, 1);
        s.push_back(needed_letter);
        
    }

    return 0;
}

