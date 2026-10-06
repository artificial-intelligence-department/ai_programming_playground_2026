/*Epic 2 - Стипендія
Данило Бурбан
Ші - 14*/
#include <iostream>

using namespace std;

int main(){
    int n;
    bool isNormal = false;
    bool isNo = false;
    cin>>n;
    for (int i = 0;i<n;i++){
        int a;
        cin>>a;
        if(a<90&&a>=51){
                isNormal = true;
        }else if(a<51){
                isNo = true;
        }
    }

    if (isNo){
        cout<<"Zabud pro stypendiiu";
    }else if(isNormal){
        cout<<"Zvychaina";
    }else{
        cout<<"Pidvyshchena";
    }
    
    return 0;
}
