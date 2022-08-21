def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1

    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)


def print_array(arr):
    for item in arr:
        print(item, end=" ")
    print()


if __name__ == "__main__":
    test = [10, 7, 8, 9, 1, 5]
    N = len(test)
    quick_sort(test, 0, N - 1)
    print("Sorted array:")
    print_array(test)
