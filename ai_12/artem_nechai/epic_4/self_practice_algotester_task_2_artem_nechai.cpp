#include <iostream>

using namespace std;

int* sort_up_2d(int* arr, int* arr1, int n) {
    int* read_from = arr;
    int* write_to = arr1;
    int* t;

    int step = 4;
    int step_half = 2;
    int i, i_write_to, i1, i2, i1_end, i2_end;
    while (step_half < n) {
        i_write_to = 0;

        for (i = 0; i + step_half < n; i += step) {
            i1 = i;
            i1_end = i + step_half;
            i2 = i1_end;
            i2_end = i + step;
            if (i2_end > n) i2_end = n;

            while (i1 < i1_end && i2 < i2_end) {
                if (read_from[i1] < read_from[i2]) {
                    write_to[i_write_to++] = read_from[i1++];
                    write_to[i_write_to++] = read_from[i1++];
                } else {
                    write_to[i_write_to++] = read_from[i2++];
                    write_to[i_write_to++] = read_from[i2++];
                }
            }

            if (i1 == i1_end) {
                i1 = i2;
                i1_end = i2_end;
            }
            for (i1; i1 < i1_end; ++i1)
                write_to[i_write_to++] = read_from[i1];
        }

        for (i; i < n; ++i)
            write_to[i] = read_from[i];

        step_half = step;
        step <<= 1;

        t = read_from;
        read_from = write_to;
        write_to = t;
    }

    return (read_from == arr) ? arr : arr1;
}

int arr_possible[30*100000*2];
int arr_possible1[30*100000*2];

int main() {
    int n;
    cin >> n;

    int arr1[100000];
    for (int i = 0; i < n; ++i)
        cin >> arr1[i];
    
    int arr_possible_count = 0;

    int new_value;
    for (int i = 0; i < n; ++i) {
        new_value = arr1[i];
        
        while(new_value > 1) {
            arr_possible[arr_possible_count++] = new_value;
            arr_possible[arr_possible_count++] = 1 + new_value - (new_value >> 1);
            new_value >>= 1;
        }
    }

    int* arr = sort_up_2d(arr_possible, arr_possible1, arr_possible_count);
    
    int a;
    long long total_time = 0;
    for (int i = 0; i < n; ++i) {
        a = arr1[i];
        while (a > 1) {
            a >>= 1;
            ++total_time;
        }
    }
    long long best_time = total_time;

    int prev_a_main = 1;
    int cur_a_main;
    for (int a_main_i = 0; a_main_i < arr_possible_count; a_main_i+=2) {
        cur_a_main = arr[a_main_i];
        total_time += 1LL * n * (cur_a_main - prev_a_main)
             - arr[a_main_i + 1];

        prev_a_main = cur_a_main;

        if (total_time < best_time)
            best_time = total_time;
    }

    cout << best_time;

    return 0;
}