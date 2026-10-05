/*
lab1 task 1 v-13
Artem Mnikh
AI_14
*/
#include <iostream>
#include <iomanip> 


using namespace std;

int main(){
    float a1 = 1000.0f;
    float b1 = 0.0001f;

    float fl_1 = (a1 - b1) * (a1 - b1);
    float fl_2 = a1 * a1;
    float fl_3 = 2 * a1 * b1;
    float fl_4 = b1 * b1;


    float float_step_1 = fl_2 - fl_3;
    float float_step_2 =  fl_1 - float_step_1;
    float float_result = float_step_2 / fl_4;


    double a2 = 1000.0;
    double b2 = 0.0001;

    double db_1 = (a2 - b2) * (a2 - b2);
    double db_2 = a2 * a2;
    double db_3 = 2 * a2 * b2;
    double db_4 = b2 * b2;

    double double_step_1 = db_2 - db_3;
    double double_step_2 = db_1 - double_step_1;
    double double_result = double_step_2 / db_4;
        cout << fixed << setprecision(8);
    cout << "Результат float: " << float_result << "\n";
    cout << "Результат double: " << double_result << "\n";
    return 0;
}