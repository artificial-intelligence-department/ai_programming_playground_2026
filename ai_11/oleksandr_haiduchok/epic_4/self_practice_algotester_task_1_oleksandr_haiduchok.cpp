#include <iostream>
#include <limits>
using namespace std;
int main(){
int n = 0;
cin >> n;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
char* s = new char[100005];
cin.getline(s, 100005);
long long len = 0;
long long count = 0;
while (*(s + len) != '\0'){
    if(*(s + len) == ' ' || *(s + len) == '\\'){
    count++;
    }
    len++;
}
long long countr = 0;
if(len > n){
    cout << "0";
    delete[] s;
    return 0;
}
if(count == 0){
    cout << "-1";
    delete[] s;
    return 0;
}
else{
    while(len <= n){
        len += count;
        count = count * 2;
        countr++;
    }
   cout << countr;

}
delete [] s;
s = nullptr;
return 0;
}

