#include <iostream>

using namespace std;

void output(bool isMin, int levelSecurity, string levelName,char isDigit, char isSpecial){
    string recomendation;
    switch(levelSecurity){
        case 1:
            recomendation="Пароль надто короткий. Мінімум 8 символів.";
            break;
        case 2:
            recomendation="Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
            break;
        case 3:
            recomendation="Додайте ще один тип символів або збільште довжину до 12.";
            break;
        case 4:
            recomendation="Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
            break;
        case 5:
            recomendation="Відмінно. Змінювати нічого не потрібно.";
            break;   
        default:
            recomendation = "default";
            break;         
    }
    //вивід
    cout<<endl<<"Мінімальні вимоги: "<< (isMin ? "ПРОЙДЕНО":"НЕ ПРОЙДЕНО");
    cout<<endl<<"Рівень надійності: "<<levelSecurity<<" - "<<levelName<<endl;
    cout<<recomendation<<endl;
    cout<<((isDigit=='n'&&isSpecial=='n')?"Попередження: пароль тільки з літер підбирається швидше.":"")<<endl;
}
int main(){
    int n=0;//к-ксть символів
    char isD;//чи є цифри
    char isB;//чи є великі літери
    char isS;//чи є спец сиволи
    bool isMin=false;

    //блок вводу та перевірки вводу
    cout<<"Довжина пароля: ";
    cin>>n;
    if(cin.fail() || n<1||n>64) {
        cout<<"Помилка: довжина мусить бути від 1 до 64.";
        return 1;
    }
    cout<<"Чи є цифри (y/n): ";
    cin>>isD;
    if(isD!='y' && isD!='n') {
        cout<<"Помилка: ввід мусить бути y або n.";
        return 1;
    }
    cout<<"Чи є великі літери (y/n): ";
    cin>>isB;
    if(isB!='y' && isB!='n') {
        cout<<"Помилка: ввід мусить бути y або n.";
        return 1;
    }
    cout<<"Чи є спеціальні символи (y/n): ";
    cin>>isS;
    if(isS!='y' && isS!='n') {
        cout<<"Помилка: ввід мусить бути y або n.";
        return 1;
    }

    //визначення скільки видів символів
    int numTypes=0;
    if(isD=='y'){
       numTypes++;
    }
    if(isB=='y'){
       numTypes++;
    }
    if(isS=='y'){
       numTypes++;
    }
    //перевірка мінімальних вимог
    if(n>=8 && numTypes>=2){
      isMin=true;
    }
    
    //визначення рівня безпеки паролю
    int level=0;
    string levelName;
    if(n<6){
        level=1;
        levelName="Дуже слабкий";
    }
    else if(n<8 || numTypes==0){
    level = 2;
    levelName="Слабкий";
    }
    else if(numTypes==1){
        level=3;
        levelName="Середній";
    }
    else if(n>=12&&numTypes==3){
        level=5;
        levelName="Дуже надійний";
    }
    else{
        level=4;
        levelName="Надійний";
    }
    
    output(isMin, level, levelName, isD, isS);
    return 0;
}