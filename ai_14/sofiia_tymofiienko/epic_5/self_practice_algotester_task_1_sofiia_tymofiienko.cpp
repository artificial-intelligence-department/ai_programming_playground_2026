#include <iostream>
using namespace std;
int parent[100005];

int  find(int x){
    if(parent[x]==x){
        return x;
    }else{
        return parent[x]=find(parent[x]);
    }
}
    int main(){
        int n, m;
        cin>>n>>m;
         int components=n;
        for (int j=1; j<=n; j++){
            parent[j]=j; 
        }
        for(int i=0; i<m; i++){
            int a, b;
            cin>>a>>b;
             int boss_a=find(a);
        int boss_b=find(b);
            if (boss_a != boss_b){
                parent[boss_b]=boss_a;
                    components--;
            }
                cout<<components<<endl;
    }
        return 0;
    }
    