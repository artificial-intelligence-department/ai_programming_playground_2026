#include <iostream>
using namespace std;

int main() {
char* s = new char[100000];
cin >> s;
if( cin.fail()){
    delete[] s;
     return 0;
}

int size = 0; // лічильник для кількості букв
while (s[size] != '\0'){
    size ++;
}

int count = 1;
for( int i = 0; i < size; ++i ){
    if(s[i] == s[i+1]){
        count++;
    } else {
        cout << s[i];

        if (count > 1){
            cout << count;
        }
        count = 1;
    }
}
cout << endl;

    delete[] s;
    s = nullptr;
    return 0;
}