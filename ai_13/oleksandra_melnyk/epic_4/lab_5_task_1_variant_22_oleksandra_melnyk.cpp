#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std; 

float arithmetic(int n, int m)
{
    float armean=0;
    int f[n][m];
    int sum=0;
    cout<<"Введіть елементи масиву: "<<endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin>>f[i][j];
        }
    }
    for (int i=0; i<n; i++){
        sum+=f[i][0];
    }
    armean=float(sum)/n;
    cout<<"Середнє арифметичне 1 стовпця: "<<armean<<endl;
    for (int j=1; j<m; j++){
        int k=0;
        for (int i=0; i<n; i++) {
            if (f[i][j]>armean) {
                k++;
            }
        }
        cout<<"У стовпці "<<j+1<<" кількість елементів, більших за середнє попереднього: " << k << endl;
        sum=0;
        for (int i=0; i<n; i++) {
            sum+=f[i][j];
        }
        armean=float(sum)/n;
    }
    return 0;
}
int main()
{
    int n,m,armean=0,k=0;
    cout<<"Введіть розміри масиву: "<<endl;
    cin>>n>>m;
    arithmetic(n,m);
}