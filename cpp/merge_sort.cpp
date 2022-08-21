#include <iostream>

using namespace std;

// merge is the core part of merge sort
// it is about how you merge the related part of the array into a sorted one
// typically in array situation, we copy the value from the source array in
// order, to make it sorted in a temp space then we put the value back from the
// temp space to make every one of them in a right place
void merge(int arr[], int l, int mid, int r) {
    int lp = l, rp = mid + 1;
    int temp[r - l + 1], tp = 0;

    while (lp <= mid && rp <= r)
        if (arr[lp] < arr[rp])
            temp[tp++] = arr[lp++];
        else
            temp[tp++] = arr[rp++];

    while (lp <= mid)
        temp[tp++] = arr[lp++];
    while (rp <= r)
        temp[tp++] = arr[rp++];

    for (int i = l; i <= r; i++)
        arr[i] = temp[i - l];
}

void sort(int arr[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        sort(arr, l, mid);
        sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

int main() {
    int arr[9] = {8, 9, 5, 6, 7, 4, 1, 2, 3};
    sort(arr, 0, sizeof arr / sizeof(int) - 1);

    for (int num : arr)
        cout << num << ' ';
    cout << endl;
}