/*
селф практіс завдання 2, Буквозабирання
*/
#include <iostream>
#include <string>
using namespace std;
int main(){
    int n;
    cin >> n;
    int *equal = new int[n] {false};
    for(int i = 0; i<n; i++){
        string start, end;
        cin >> start >> end;
        int moves = start.length() - end.length();//у Сірожі є шанс якщо кінцевий рядок знаходиться праворуч від точки moves/2, інакше Ларрі просто буде видаляти все зліва(відповідна ситуація справа)
        if(start == end){//ну і якщо вони просто рівні
            equal[i] = true;
        }//у випадку непарної кількості ходів останнімходить Ларрі
        else if(moves % 2 == 1){//Сірожа може компенсувати кожен крок Ларрі крім останньоготому в нас має підходити незалежно від дії Ларрі
            if((start.substr(moves/2, end.length()) == end) && (start.substr(moves/2 + 1, end.length()) == end)) equal[i] = true;
        }//ну і якщо парна то то Сірожа може компенсувати кожен крок Ларрі
        else if(start.substr(moves/2, end.length()) == end){
            equal[i] = true;
        }//ще один варіант перемоги - зліва і справа є кінцеве слово і Сірожі треба продублювати один крок Ларрі тим самим зсунути один з варіантів в центр
        else if(moves >= 2){
            if((start.substr(moves/2 - 1, end.length()) == end) && (start.substr(moves/2 + 1, end.length()) == end)) equal[i] = true;
        }
    }
    for(int i = 0; i<n; i++){
        (equal[i]) ? (cout << "Sergei" <<endl) : (cout << "Larry" <<endl);
    }
    delete[] equal;
    return 0;
}