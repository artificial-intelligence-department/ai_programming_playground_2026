/*
Задача про яблука
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    int apples = 0;
    int friends = 0; 
    int app_friends = 0;

    cin >> apples >> friends >> app_friends;
    cout << apples + (friends * app_friends);
    cout << endl;


    return 0;
}