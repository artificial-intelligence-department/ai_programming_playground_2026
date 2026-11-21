/*
Task: self_practice_algotester_task_1 (Снігурочка)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>
#include <string>


using namespace std;

bool Ispalindrom(string &word){


    int len = word.length();

    for (int i = 0; i < len; i++) {
        word[i] = tolower(word[i]);
    }


    int i = 0;
    int j = len - 1;

    while(i < j){

        if(word[i] != word[j]){
            return false;
        }
        i++;
        j--;
    }


    return true;

}


int main (){

    string word;

    int count = 0;
    while(cin >> word){
        if(Ispalindrom(word)) count++;
    }
    cout << endl;
    cout << count << endl;;


    return 0;
}