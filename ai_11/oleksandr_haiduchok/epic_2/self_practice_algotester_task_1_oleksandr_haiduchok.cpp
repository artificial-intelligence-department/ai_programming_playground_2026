#include <iostream>
using namespace std;
int main (){
int n = 0;
int a = 0;
int m = 101;
cin >> n;
bool h = true;

while (n--){
    cin >> a;
    if(a < m){
        m = a;
    }
    if(a < 90){
        h = false;
    }
}
    if(m < 51){
        cout << "Zabud pro stypendiiu\n";
    }
    else if (h){
        cout << "Pidvyshchena\n";
    }
    else{
        cout << "Zvychaina\n";
    }



return 0;
}

