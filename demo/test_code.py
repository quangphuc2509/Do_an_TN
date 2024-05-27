# Mảng 2 chiều 3x10
arr1 = [
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    [11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
    [21, 22, 23, 24, 25, 26, 27, 28, 29, 30]
]

# Mảng 2 chiều 2x4
arr2 = [
    [100, 200, 300, 400],
    [101, 201, 301, 401]
]

# Thay thế 4 giá trị đầu tiên của hàng đầu tiên trong arr1 bằng giá trị của hàng đầu tiên trong arr2
arr1[:len(arr2)] = arr2

# In mảng arr1 sau khi thay thế
for row in arr1:
    print(row)
