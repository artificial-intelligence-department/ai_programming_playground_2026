#include <iostream>
#include <iomanip>

using namespace std;


void clear_array(int rows, int *array[]) {
	for (int i = 0; i < rows; i++) {
		delete[] array[i];
	}
	delete[] array;
}


void menu_show_image(int **img, int rows, int cols, char *brightness_symbols) {
	cout << "Зображення " << rows << " x " << cols << ":" << endl;
	for (int i = 0; i < rows; i++) {
		int *row = img[i];
		for (int j = 0; j < cols; j++) {
			cout << *(row+j) << " ";
		}
		cout << endl;
	}

	cout << endl << "Малюнок:" << endl;
	
	for (int i = 0; i < rows; i++) {
		int *row = img[i];
		for (int j = 0; j < cols; j++) {
			cout << brightness_symbols[*(row+j)];
		}
		cout << endl;
	}
}


void findExtremes(int **img, int rows, int cols, int &minRow, int &maxRow, int &minCol, int &maxCol) {
	int minBrightness = **img;
	minRow = 0;
	maxRow = 0;
	minCol = 0;
	maxCol = 0;

	for (int i = 0; i < rows; i++) {
		int *row = img[i];
		for (int j = 0; j < cols; j++) {
			int value = *(row+j);
			if (value < *(img[minRow] + minCol)) {
				minRow = i;
				minCol = j;
			}
			if (value > *(img[maxRow] + maxCol)) {
				maxRow = i;
				maxCol = j;
			}
		}
	}
}


void menu_brightness_statistics(int **img, int rows, int cols) {
	int minRow, minCol, maxRow, maxCol;
	findExtremes(img, rows, cols, minRow, maxRow, minCol, maxCol);
	cout << "Найтемніший піксель: " << *(img[minRow] + minCol) << " (рядок " << minRow << ", стовпець " << minCol << ")" << endl;
	cout << "Найсвітліший піксель: " << *(img[maxRow] + maxCol) << " (рядок " << maxRow << ", стовпець " << maxCol << ")" << endl;
	
	int total_brightness = 0;
	for (int i = 0; i < rows; i++) {
		int *row = img[i];
		for (int j = 0; j < cols; j++) {
			total_brightness += *(row+j);
		}
	}
	cout << fixed << setprecision(2) << "Середня яскравість: " << (float)total_brightness / (float)(rows * cols) << endl;

	cout << fixed << setprecision(1) << "Середня по рядках:";
	for (int i = 0; i < rows; i++) {
		int *row = img[i];
		int row_brightness = 0;
		for (int j = 0; j < cols; j++) {
			row_brightness += *(row+j);
		}
		cout << " " << (float)row_brightness / (float)cols;
	}
	cout << endl;
}


void menu_invert_brightness(int **img, int rows, int cols) {
	cout << "Яскравість інвертовано." << endl;
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			img[i][j] = 9 - img[i][j];
			cout << img[i][j] << " ";
		}
		cout << endl;
	}
}


void swapPixels(int *a, int *b) {
	int t = *b;
	*b = *a;
	*a = t;
}


void menu_mirror_horizontal(int **img, int rows, int cols) {
	cout << "Зображення віддзеркалено." << endl <<
		"Початкове:" << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << img[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < rows; i++) {
		int *row = img[i];
		for (int j = 0; j < (cols+1) / 2; j++) {
			swapPixels(row+j, row+cols-j-1);
		}
	}

	cout << endl << "Результат:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << img[i][j] << " ";
		}
		cout << endl;
	}
}


int** rotateRight(int **img, int &rows, int &cols) {
	int t = cols;
	cols = rows;
	rows = t;

	int **img_new = new int*[rows];

	for (int i = 0; i < rows; i++) {
		img_new[i] = new int[cols]; 

		for (int j = 0; j < cols; j++) {
			img_new[i][j] = img[cols-j-1][i];
		}
	}

	clear_array(cols, img);

	return img_new;
}


void menu_rotate_90_degree_clockwise(int **&img, int &rows, int &cols) {
	img = rotateRight(img, rows, cols);

	cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
	for (int i = 0; i < rows; i++) {
		int *row = img[i];
		for (int j = 0; j < cols; j++) {
			cout << *(row+j) << " ";
		}
		cout << endl;
	}
}



int main() {
	cout << "Висота зображення: ";
	int rows;
	cin >> rows;
	if (cin.fail() || rows < 1 || rows > 20) {
		return 0;
	}

	
	cout << "Ширина зображення: ";
	int cols;
	cin >> cols;
	if (cin.fail() || cols < 1 || cols > 20) {
		return 0;
	}
	cin.ignore(256, '\n');


	int **image = new int*[rows];

	for (int i = 0; i < rows; i++) {
		image[i] = new int[cols]; 

		for (int j = 0; j < cols; j++) {
			int value;
			cin >> value;
			if (cin.fail() || value < 0 || value > 9) {
				clear_array(i + 1, image);
				return 0;
			}

			image[i][j] = value;
		}
	}

	char brightness_symbols[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

	
	int chosen_action;
	bool is_working = true;
	while (is_working) {
		cout << "Вибиріть операцію:" << endl <<
			"Пункт  Операція" << endl <<
			"1      Показати зображення" << endl <<
			"2      Статистика яскравості" << endl <<
			"3      Інвертувати яскравість" << endl <<
			"4      Віддзеркалити по горизонталі" << endl <<
			"5      Повернути на 90 градусів праворуч" << endl <<
			"0      Вихід" << endl;

		cin >> chosen_action;
		if (cin.fail() || chosen_action < 0 || chosen_action > 5) {
			break;
		} 
		cout << endl;

		if (chosen_action == 1) {
			menu_show_image(image, rows, cols, brightness_symbols);

		} else if (chosen_action == 2) {
			menu_brightness_statistics(image, rows, cols);

		} else if (chosen_action == 3) {
			menu_invert_brightness(image, rows, cols);

		} else if (chosen_action == 4) {
			menu_mirror_horizontal(image, rows, cols);

		} else if (chosen_action == 5) {
			menu_rotate_90_degree_clockwise(image, rows, cols);

		} else {
			is_working = false;
		}
		
		cout << endl;
	}

	clear_array(cols, image);

	return 0;
}