/* Мінімальні вигуки №0877
Artem Mnikh 
AI_14
*/

#include <iostream>

using namespace std;

int main(){
    int n;
    int counter = 1;
    cin >> n;
    long num, temp_num;
    cin >> temp_num;
    for (int i = 1; i < n; ++i){
        cin >> num;
        if (num <= temp_num){ counter++;
        temp_num = num;
        }
    }
    cout << counter;
    return 0;
}