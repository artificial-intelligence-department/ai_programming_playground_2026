#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool ispal(string w){
    int n=w.length();
    for (int i=0; i<n/2; i++){
        if (tolower((unsigned char)w[i])!=tolower((unsigned char)w[n-1-i])){
            return false;
        }
    }
    return true;
}

int main()
{
    string word;
    int count=0;

    while (cin>>word){
        if (ispal(word)){
            count++;
        }
    }
    cout<<count<<'\n';
}

