#include <iostream>
using namespace std;
int num[100004];
int Root(int a){
    if(a == num[a]){
        return a;
    }
    return Root(num[a]);
}
int main(){
    int n = 0;
    int m = 0;
    int a = 0;
    int b = 0;
    cin >> n >> m;
    for(int j = 1; j <= n; j++){
        num[j] = j;
    }
    int comp = n;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        if(Root(a) != Root(b)){
            num[Root(b)] = Root(a);
            comp--;
        }
        
        cout << comp << "\n";
    }
    return 0;
}