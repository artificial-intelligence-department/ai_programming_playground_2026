#include <iostream>
using namespace std;

int main(){

int n;
cin >> n;
    if(n < 0 || n > 100000){
        return 1;
    }

int N[100000];
    for(int i = 0;i < n;i++){
        cin >> N[i];
    }

int a,b,c;
cin >> a >> b >> c;
    if(a < 0 || a > 100000 || b < 0 || b > 100000 || c < 0 || c > 100000){
        return 1;
    }

int count = 0;
    for (int i = 0;i < n;i++){
        if(N[i] != a && N[i] != b && N[i] != c){
            N[count] = N[i];
            count++;
        }
}

int res[100000]; 
    for(int i = 0;i < count - 1;i++){
        res[i] = N[i] + N[i + 1];
    }

int newSize;
    if(count > 0){
        newSize = count - 1;
    }else{
        newSize = 0;
    }
cout <<newSize << endl;

for(int i = 0;i < newSize;i++){
    cout <<res[i] <<" ";
}
    

return 0;
}