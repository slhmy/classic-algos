#include <iostream>

using namespace std;

void placePivotAtEnd(int arr[], int left_bound_idx, int right_bound_idx) {
    // Select the pivot from left, right and middle element
    int middle_idx = (left_bound_idx + right_bound_idx) / 2;

    // Do the sort of the three elements
    if (arr[left_bound_idx] > arr[middle_idx])
        swap(arr[left_bound_idx], arr[middle_idx]);
    if (arr[left_bound_idx] > arr[right_bound_idx])
        swap(arr[left_bound_idx], arr[right_bound_idx]);
    if (arr[middle_idx] > arr[right_bound_idx])
        swap(arr[middle_idx], arr[right_bound_idx]);

    // Move the pivot to the end of the array
    swap(arr[middle_idx], arr[right_bound_idx]);
}

void placePivotAtEndNothing(int arr[], int left_bound_idx,
                            int right_bound_idx) {
    // Do nothing
}

// Separate the array into two parts
// One is smaller than the pivot, the other is larger than the pivot
// Return the index of the pivot
int partition(int arr[], int left_bound_idx, int right_bound_idx) {
    // Select the pivot
    // Normally, we place the pivot at the end of the array
    // and start picking elements from [left_bound_idx, right_bound_idx - 1]
    placePivotAtEnd(arr, left_bound_idx, right_bound_idx);
    int pivot = arr[right_bound_idx];

    // Prepare a index pointer to store the last element that is smaller than
    // the pivot
    int left_arr_ptr = left_bound_idx - 1;
    // Find the elements that are smaller than the pivot and move them to the
    // left part
    for (int i = left_bound_idx; i < right_bound_idx; i++)
        if (arr[i] < pivot) {
            // The worst case is that left_arr_ptr == i
            // Otherwise, left_arr_ptr < i, which means arr[left_arr_ptr] >=
            // pivot
            left_arr_ptr = left_arr_ptr + 1;
            swap(arr[left_arr_ptr], arr[i]);
        }

    // Move the pivot to the right position
    swap(arr[left_arr_ptr + 1], arr[right_bound_idx]);
    return left_arr_ptr + 1;
}

void quickSort(int arr[], int left_bound_idx, int right_bound_idx) {
    // If there are more than one element in the range
    if (left_bound_idx < right_bound_idx) {
        // Separate the array into two parts by selecting a pivot from the array
        // One is smaller than the pivot, the other is larger than the pivot
        int pivot_idx = partition(arr, left_bound_idx, right_bound_idx);

        // Recursively sort the two parts
        // Pivot don't need to be moved, since it's already in the right
        // position
        quickSort(arr, left_bound_idx, pivot_idx - 1);
        quickSort(arr, pivot_idx + 1, right_bound_idx);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    cout << "Sorted array: \n";
    printArray(arr, n);
    return 0;
}