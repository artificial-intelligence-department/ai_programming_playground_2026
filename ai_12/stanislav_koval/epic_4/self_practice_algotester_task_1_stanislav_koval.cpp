/*
Алготестер Поле чудес
Станіслав Коваль
ШІ-12
*/

#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    char arr[s.length()];
    arr[0]=s[0];
    int count =1;
    for (int i = 0; i < s.length(); i++){
        bool per = true;
        for (int j = 0; j < count; j++){
            if (arr[j]==s[i]){
                per = false;
            }
        }
        if(per){
            arr[count]=s[i];
            count++;
        }
    }

    cout << count << endl;
    return 0;
}