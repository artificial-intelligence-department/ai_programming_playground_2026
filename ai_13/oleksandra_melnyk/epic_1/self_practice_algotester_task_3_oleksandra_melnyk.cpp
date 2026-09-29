#include <iostream>
#include <string>
using namespace std;
int main()
{
    string n;
    cin>>n;
    string maxx=n;
    string minn=n;
    for (int i=0; i<n.length(); i++)
    {
        if (n[i]=='*'){
            if (i==0){
                minn[i]='1';
            }
            else{
                minn[i]='0';
            }
          maxx[i]='9';  
        }
    }
    cout<<minn<<" "<<maxx;
}



