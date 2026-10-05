# include <iostream>

using namespace std;
int main(){
    // Введення довжини пароля
    int length;
    cout << "Password length: ";
    cin >> length;
    // Перевірка коректності довжини
    if (length<1|| length >64){
        cout<<"Error: password length must be from 1 to 64"<<endl;
        return 1;
    }
    
    char hasDigits;
    cout<<"Has digits (y/n):";
    cin >> hasDigits;
    if (!(hasDigits == 'y' ||hasDigits =='n')){
        cout<<"Error: enter 'y' or 'n'"<<endl;
        return 1;
    }
    char hasUppercase;
    char hasSpecial;
    cout<<"Has uppercase letters(y/n):";
    cin>>hasUppercase;
    if (!(hasUppercase == 'y' ||hasUppercase =='n')){
        cout<<"Error: enter 'y' or 'n'"<<endl;
        return 1;
    }

    cout<<"Has special characters (y/n):";
    cin>>hasSpecial;
    if (!(hasSpecial == 'y' ||hasSpecial =='n')){
        cout<<"Error: enter 'y' or 'n'"<<endl;
        return 1;
    }
    // Підрахунок кількості типів символів
    int typesCount = 0;
    if (hasDigits == 'y') typesCount++;
    if (hasUppercase == 'y') typesCount++;
    if (hasSpecial == 'y') typesCount++;

    // Перевірка мінімальних вимог
    if (length >=8 && typesCount >=2){
        cout<<"Minimum requirements: PASSED"<<endl;
    } else {
        cout<<"Minimum requirements: not PASSED"<<endl;
    }
    // Визначення рівня надійності пароля
    int level;
    if (length <6){
        level = 1;
    } else if (length <8 || typesCount ==0){
        level = 2;
    } else if (typesCount == 1){
        level = 3;
    } else if (length >=12 && typesCount == 3){
        level = 5;
    } else{
        level = 4;
    }
    // Виведення рекомендації залежно від рівня
        switch (level)
        {
            case 1:
            cout<< "Level:1 - Very weak password."<<endl;
            cout << "Password is too short. Minimum length is 8 characters."<<endl;
            break;
            case 2:
            cout<< "Level:2 - Weak password."<<endl;
            cout << "Increase the length to 8+ characters and add digits, uppercase letters or special characters."<<endl;
            break;
            case 3:
            cout<<"Level:3 - Medium password."<<endl;
            cout<<"Add one more character type or increase the length to 12."<<endl;
            break;
            case 4:
            cout<<"Level:4 - Reliable password."<<endl;
            cout<<"Good password. For maximum security use 12+ characters and all character types."<<endl;
            break;
            case 5:
            cout<<"Level:5 - Very reliable password."<<endl;
            cout<<"Excellent password. No changes needed."<<endl;
            break;

            default:
            cout<< " No recommendation yet."<<endl;
            break;
        }
            // Попередження для пароля лише з літер
            if (hasDigits == 'n' && hasSpecial == 'n')
            {
                cout<< "Warning: password is weak. Consider adding digits or special characters."<<endl;
            }


        



    
    return 0;

    
}
