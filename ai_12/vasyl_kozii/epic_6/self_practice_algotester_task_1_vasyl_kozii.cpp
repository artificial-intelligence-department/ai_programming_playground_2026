/*
Self Practice Algotester Task 1
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
using namespace std;
int parent[100005];
int sz[100005];
int findRoot(int i) {
    if (parent[i]==i)
        return i;
    return parent[i]=findRoot(parent[i]);
}
bool unionSets(int i, int j) {
    int rootI=findRoot(i);
    int rootJ=findRoot(j);
    if (rootI!=rootJ)
    {
        if (sz[rootI] < sz[rootJ])
        {
            int t=rootI;
            rootI=rootJ;
            rootJ=t;
        }
        parent[rootJ]=rootI;
        sz[rootI]+=sz[rootJ];
        return true;
    }
    return false;
}
int main() {
    int n, m;
    cin >>n >>m;
    int A[m];
    int B[m];
    for (int i=0; i<m; i++)
    {
        cin >>A[i] >>B[i];
    }
    for (int i=1; i<=n; i++)
    {
        parent[i]=i;
        sz[i]=1;
    }
    int components=n;
    for (int i=0; i<m; i++)
    {
        if (unionSets(A[i], B[i])) {
            components--;
        }
        cout <<components <<"\n";
    }
}