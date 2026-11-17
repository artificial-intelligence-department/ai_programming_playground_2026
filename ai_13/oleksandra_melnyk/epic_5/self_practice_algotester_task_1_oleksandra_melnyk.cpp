#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    char c;
    cin>>n>>c;
    string best;
    for (int i=0; i<n; i++){
        string s;
        cin>>s;
        int len=s.length();
        int pos=0;
        while (pos<len && s[pos]<=c){
            pos++;
        }

        string t=s;
        t.insert(pos,1,c);
        if (i==0 || t<best){
            best=t;
        }
    }
    cout<<best<<'\n';
}
