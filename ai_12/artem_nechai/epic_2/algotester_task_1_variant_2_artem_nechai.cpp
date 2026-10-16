#include <iostream>

using namespace std;
int main()
{
	long long h[4];
	long long d[4];

	bool stay = true;
	long long h_max = 0;

	// Enter height of each legs
	for (int i = 0; i != 4; i++) {
		cin >> h[i];
		if (h[i] > h_max) {
			h_max = h[i];
		}
	}

	// Find h_min
	long long h_min = h_max;
	for (int i = 0; i != 4; i++) {
		if (h[i] < h_min) {
			h_min = h[i];
		}
	}

	// Enter cut of each legs
	for (int i = 0; i != 4; i++) {
		cin >> d[i];
	}

	for (int i = 0; i != 4; i++) {
		if (d[i] > h[i]) {
			cout << "ERROR";
			return 0;
		}

		h[i] -= d[i];
		if (h[i] < h_min) {
			h_min = h[i];
		}

		h_max = 0;
		for (int a = 0; a != 4; a++) {
			if (h[a] > h_max) {
				h_max = h[a];
			}
		}

		if (h_max >= 2 * h_min) {
			stay = false;
		}
	}
	if (stay) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	return 0;
}
