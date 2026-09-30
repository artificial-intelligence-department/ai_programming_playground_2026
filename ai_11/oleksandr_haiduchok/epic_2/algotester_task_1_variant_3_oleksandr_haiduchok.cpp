#include <iostream>
#include <cmath>

using namespace std;
int main(){
long long a,b,c,d,e = 0;
cin >> a;
if (a < 1){
    cout << "ERROR";
    return 0;
}

cin >> b;
if (b < 1){
    cout << "ERROR";
    return 0;
}
else if (a < b){
    cout << "LOSS";
    return 0;
}
cin >> c;
if (c < 1){
    cout << "ERROR";
    return 0;
}
else if (b < c){
    cout << "LOSS";
    return 0;
}
cin >> d;
if (d < 1){
    cout << "ERROR";
    return 0;
}
else if (c < d){
    cout << "LOSS";
    return 0;
}
cin >> e;
if (e < 1){
    cout << "ERROR";
    return 0;
}
else if (d < e){
    cout << "LOSS";
    return 0;
}

 if(a >= b && b >= c && c >= d && d >= e){
    cout << "WIN";
 }
return 0;
}
