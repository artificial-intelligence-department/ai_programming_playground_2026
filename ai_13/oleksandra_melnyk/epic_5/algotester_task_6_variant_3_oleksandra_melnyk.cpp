#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    cin>>n;
    string r[9];
    for (int i=0; i<n; i++){
        cin>>r[i];
    }
    int q;
    cin>>q;
    for (int j=0; j<q; j++){
        int x,y;
        cin>>x>>y;
        x--;
        y--;
        if (j>0){
            cout<<'\n';
        }
        char c=r[x][y];
        if (c!='0'){
            cout<<1<<'\n'<<c<<'\n';
            continue;
        }
        bool w[10]={false};
        for (int t=0; t<n; t++){
            w[r[x][t]-'0']=true;
        }
        for (int i=0; i<n; i++){
            w[r[i][y]-'0']=true;
        }
        int count=0;
        for (int s=1; s<=n; s++){
            if (!w[s]){
                count++;
            }
        }
        cout<<count<<'\n';
        if(count>0){
            bool first=true;
            for (int s=1; s<=n; s++){
                if (!w[s]){
                    if (!first){
                        cout<<" ";
                    }
                    cout<<s;
                    first=false;
                }
            }
            cout<<'\n';
        }
    }
}