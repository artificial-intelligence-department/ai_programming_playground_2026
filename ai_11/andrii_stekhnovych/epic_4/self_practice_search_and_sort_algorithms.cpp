#include <iostream>
#include <cstring>
using namespace std;
void Merge(int array[], int left[], int right[], int left_size, int right_size) {
    int i=0, j=0, k=0;
    while (i<left_size && j<right_size) {
        if (left[i]<right[j]) {
            array[k]=left[i];
            i++;
        } else {
            array[k]=right[j];
            j++;
        }
        k++;
    }
    while (i<left_size) {
        array[k]=left[i];
        i++;
        k++;
    }
    while (j<right_size) {
        array[k]=right[j];
        j++;
        k++;
    }
}
void MergeSort(int array[], int array_length) {
    if (array_length<2) {
        return;
    }
    int mid=array_length/2;
    int left[mid];
    int right[array_length-mid];
    for (int i = 0; i<mid; i++) {
        left[i]=array[i];
    }
    for (int j=mid; j<array_length; j++) {
        right[j-mid]=array[j];
    }
    MergeSort(left, mid);
    MergeSort(right, array_length-mid);
    Merge(array, left, right, mid, array_length-mid);
}
int partition(int array[], int left, int right) {
    int pivot = array[right];
    int i=left-1;
    for (int j=left; j<right; j++) {
        if(array[j]<pivot) {
            i++;
            int b = array[i];
            array[i]=array[j];
            array[j]=b;

        }
    }
    int b=array[right];
    array[right]=array[i+1];
    array[i+1]=b;
    return i+1;

}
void QuickSort(int array[], int left, int right) {
    if (left<right) {
        int pivot_pos = partition(array, left, right);
        QuickSort(array, left, pivot_pos-1);
        QuickSort(array, pivot_pos+1, right);
    }
    return;
}
int InterpolationSearch(int array[], int array_length, int target) {
    int left=0;
    int right=array_length-1;
    while (left<=right) {
        int probe = left + (right-left)*((target-array[left])/(array[right]-array[left]));
        if (array[probe]==target) {
            return probe; 
        } else if (array[probe]<target) {
            left=probe+1;
        } else {
            right=probe-1;
        }
    }
    return -1;
}