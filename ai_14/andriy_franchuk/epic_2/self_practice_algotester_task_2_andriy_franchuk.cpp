/*Epic 2 - Стипендія
Франчук Андрій
Ші - 14*/

#include <iostream>
#include <string>

using namespace std;

int main(){
    int n = 0;
    if(!(cin >> n) || n < 1 || n > 7){
        cout << "Кількість іспитів має бути від 1 до 7";
        return 0;
    }

    bool fail = false;
    bool excellent = true;

    for (int i = 0; i < n; i++){
        int grade = 0;
        cin >> grade;

        if (grade < 90){
            excellent = false;
        }

        if (grade < 51){
            fail = true;
        }
    }

    if (fail){
        cout << "Zabud pro stypendiiu" << endl;
    }else if(excellent){
        cout << "Pidvyshchena" << endl;
    }else{
        cout << "Zvychaina" << endl;
    }
    return 0;
}