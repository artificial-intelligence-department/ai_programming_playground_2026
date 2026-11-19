#include <iostream>
using namespace std;

int main() {
int n;
cin >> n;
if(n < 0 || n > 100){
    return 1;
}

int a[100];
for(int i = 0;i < n;i++){
    cin >> a[i];
    if(a[i] < 0 || a[i] > 100){
        return 1;
    }
}

int m;
cin >> m;
if(m < 0 || m > 100){
    return 1;
}

int b[100];
for(int i = 0;i < m;i++){
    cin >> b[i];
    if(b[i] < 0 || b[i] > 100){
        return 1;
    }
}
int count = 0;
    for(int i = 0;i < n;i++){
     for(int j = 0;j < m;j++){
         if(a[i] == b[j]){
            count++;
        }
    }
}
    cout << count << endl;

int unique = n + m -count;
    cout << unique;

return 0;
}