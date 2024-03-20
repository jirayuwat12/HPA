import threading
import psutil

def threaded_merge_sort(arr, threads=2):
    if threads <= 1 or len(arr) <= 10000000:
        return arr.sort()
    else:
        mid = len(arr) // 2
        left_arr = arr[:mid]
        right_arr = arr[mid:]
        left = threading.Thread(target=threaded_merge_sort, args=(left_arr, threads // 2))
        right = threading.Thread(target=threaded_merge_sort, args=(right_arr, threads // 2))
        left.start()
        right.start()
        left.join()
        right.join()
        i = j = k = 0
        while i < len(left_arr) and j < len(right_arr):
            if left_arr[i][0] < right_arr[j][0]:
                arr[k] = left_arr[i]
                i += 1
            else:
                arr[k] = right_arr[j]
                j += 1
            k += 1
        while i < len(left_arr):
            arr[k] = left_arr[i]
            i += 1
            k += 1
        while j < len(right_arr):
            arr[k] = right_arr[j]
            j += 1
            k += 1
    return arr

if __name__ == '__main__':
    cores = psutil.cpu_count()
    l = []
    with open('sort-rand-19999999.txt') as f:
        for line in f:
            id, value = line.strip().split(': ')
            l.append((float(value), int(id[4:])))
    l = threaded_merge_sort(l, cores)
    print('Sorted!')
