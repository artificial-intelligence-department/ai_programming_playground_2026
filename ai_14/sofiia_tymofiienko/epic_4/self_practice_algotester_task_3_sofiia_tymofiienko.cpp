#include <iostream>
#include <string>
using namespace std;
int main(){
string s;
cin>>s;
int cnt[256]={0};
for (int n=0; n<s.size(); n++){
    cnt[s[n]]++;
}
bool hid=false;
for (int j=0; j<256; j++){
    if (cnt[j]%2==1){
        hid=true;
    }
}
if (!hid){
    cout<<"2"<<endl;
}else{
    cout<<"1"<<endl;
    for (int i=0; i<256; i++){
         if (cnt[i]%2==1){
            cout<<(char)i;
         }
    }
    cout<<endl;
}
    return 0;
}
