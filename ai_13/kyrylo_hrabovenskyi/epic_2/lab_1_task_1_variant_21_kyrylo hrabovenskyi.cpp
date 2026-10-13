/*
Лабораторна робота 1 варіант 21
Грабовенський Кирило ШІ-13 task 1
*/
#include <iostream> 

using namespace std;

int main()
{
	// =========================================================================
	// СТРУКТУРНИЙ БЛОК 1: ОБЧИСЛЕННЯ З ВИКОРИСТАННЯМ ТИПУ DOUBLE (ПОДВІЙНА ТОЧНІСТЬ)
	// (Покрокове розбиття математичного виразу для збереження високої точності)
	// =========================================================================
	cout << "For double\n";

	double a_d = 100;
	double b_d = 0.001;

	double first_task_d = pow(a_d - b_d, 4);
	double second_task_d = pow(a_d, 4) - 4 * pow(a_d, 3) * b_d;
	double third_task_d = second_task_d + 6 * pow(a_d, 2) * pow(b_d, 2);
	double forth_task_d = first_task_d - third_task_d;

	double fifth_task_d = pow(b_d, 4) - 4 * a_d * pow(b_d, 3);

	double result_d = forth_task_d / fifth_task_d;
	cout << result_d;

	// =========================================================================
	// СТРУКТУРНИЙ БЛОК 2: ОБЧИСЛЕННЯ З ВИКОРИСТАННЯМ ТИПУ FLOAT (ОДИНАРНА ТОЧНІСТЬ)
	// (Аналогічні математичні дії, які демонструють втрату точності через специфіку float)
	// =========================================================================
	cout << "\nfor float\n";

	float a_f = 100;
	float b_f = 0.001;

	float first_task_f = pow(a_f - b_f, 4);
	float second_task_f = pow(a_f, 4) - 4 * pow(a_f, 3) * b_f;
	float third_task_f = second_task_f + 6 * pow(a_f, 2) * pow(b_f, 2);
	float forth_task_f = first_task_f - third_task_f;

	float fifth_task_f = pow(b_f, 4) - 4 * a_f * pow(b_f, 3);

	float result_f = forth_task_f / fifth_task_f;
	cout << result_f;
}