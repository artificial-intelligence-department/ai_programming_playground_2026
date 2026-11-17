/*Algotester Task 6 Variant 3
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
using namespace std;
int main(){
    int N, Q;
    cin>>N;
    string row[10];
    for(int i=0; i<N; i++){
        cin>>row[i];
    }
    cin>>Q;
    for (int i = 0; i < Q; i++) {
        int x, y;
        cin>>x>>y;
        cout<<endl<<endl;
        x--;
        y--;
        bool usedplaces[10]={false};
        if (row[x][y] != '0') {
            cout<< 1 <<endl<< row[x][y] <<endl;
        } else {
            for (int j=0; j < N; j++) {
                if (j==y) continue; 
                int digit=row[x][j] - '0'; 
                if (digit>=1 && digit<=N) {
                    usedplaces[digit]=true; 
                }
            }
            
            for (int r=0; r < N; r++) {
                if (r==x) continue; 
                int digit=row[r][y] - '0';
                if (digit>=1 && digit<=N) {
                    usedplaces[digit]=true;
                }
            }
            int count=0;
            for(int k=1; k<=N; k++){
                if(!usedplaces[k]) count++;
            }
            cout<<count<<endl;
            if (count>0) {
                bool first=true; 
                for (int d=1; d<=N; d++) {
                    if (!usedplaces[d]) {
                        if (!first) {
                            cout<<" "; 
                        }
                        cout<<d;
                        first=false;
                    }
                }
                cout<<endl;
            }
        }
    }
    return 0;
}