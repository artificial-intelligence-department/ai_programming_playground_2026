/*Epic 4 - Інтерактивне число
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main() {
    int left = 1;
    int right = 1000000000;
    
    while (left <= right){
        int mid = (left + right) / 2;
        cout << mid << endl;
        
        string response;
        cin >> response;
        
        if (response == "=") {
            break;
        } else if (response == "<") {
            left = mid + 1;
        } else if (response == ">") {
            right = mid - 1;
        } 
    }
    return 0;
}