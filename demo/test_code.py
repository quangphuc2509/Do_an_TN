import numpy as np

my_array = np.array([[1, 2, 3], [4, 5, 6]])
total = np.sum(my_array)
print(total)  # Kết quả là 21 (1 + 2 + 3 + 4 + 5 + 6 = 21)

# Tính tổng theo từng hàng (trục 1)
row_sum = np.sum(my_array, axis=1)
print(row_sum)  # Kết quả là [6 15]

# Tính tổng theo từng cột (trục 0)
col_sum = np.sum(my_array, axis=0)
print(col_sum)  # Kết quả là [5 7 9]
