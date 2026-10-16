#include <iostream>
using namespace std;
int main(){
    
    int n =0;
    int elves_before[1000]={0};
    cin>>n;
    for(int i = 0;i<n;i++){
        cin >> elves_before[i];
    }
    int last_elve = elves_before[n-1];
    int first_elve = elves_before[0];
    int elves_correct[1000]={0};
    for(int i = 0;i<n;i++){
        elves_correct[i]=elves_before[n-1-i];
    }
    int elves_new[1000]={0};
    for(int i = 0;i<n;i++){
        cin >> elves_new[i];
    }
    bool check = 1;
    for(int i =0 ;i<n;i++){
        if(elves_new[i]!=elves_correct[i]){
            check = 0;
            break;
        }
    }
    if (check){
        cout<<"Yes";
    }else{
        cout<<"No"<<endl;
        for (int i = 0;i<n;i++){
            cout<<elves_correct[i]<<" ";
        }

    }
    return 0;
}