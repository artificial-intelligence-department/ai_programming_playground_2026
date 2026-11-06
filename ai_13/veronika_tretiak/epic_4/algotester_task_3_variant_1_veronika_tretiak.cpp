/*
Автор: Вероніка Третяк
Задача: Алготестер №3, варіант №1
Група: ШІ-13
*/
#include <iostream>
#include <string>

using namespace std;

int main(){
int n;
cin >> n;

cin.ignore(10000, '\n');
string line;
int count = 0;
for(int i = 0; i < n; i++){
    getline(cin, line);
    bool Group = false;
    for(int j = 0; j < line.size(); j++){
        if(line[j] == '#'){
            if(!Group){
                count++;
                Group = true;
            }
        }else{
                Group = false;
            }
    }
}
cout << count << endl;

return 0;
}