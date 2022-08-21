fn partition(arr: &mut [i32], low: isize, high: isize) -> isize {
    let pivot = arr[high as usize];
    let mut i = low - 1;

    for j in low..high {
        if arr[j as usize] < pivot {
            i += 1;
            arr.swap(i as usize, j as usize);
        }
    }
    arr.swap((i + 1) as usize, high as usize);
    i + 1
}

fn quick_sort(arr: &mut [i32], low: isize, high: isize) {
    if low < high {
        let pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

fn print_array(arr: &[i32]) {
    for &item in arr.iter() {
        print!("{} ", item);
    }
    println!();
}

fn main() {
    let mut arr = [10, 7, 8, 9, 1, 5];
    let n = arr.len();
    quick_sort(&mut arr, 0, (n - 1) as isize);
    println!("Sorted array:");
    print_array(&arr);
}