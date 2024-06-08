# import math
# import socket
# import threading
# import time
# import random

# def twos_complement(binary_str):
#     # Nếu đầu vào không đủ 32 bit, bổ sung số 0 vào trước chuỗi nhị phân
#     binary_str = binary_str.zfill(32)

#     # Đảo bit của chuỗi nhị phân đã lọc
#     reversed_binary_str = ''.join('1' if bit == '0' else '0' for bit in binary_str)

#     # Cộng thêm 1
#     result = bin(int(reversed_binary_str, 2) + 1)[2:]

#     return result

# def convert_to_scientific_notation(number):


#     if number < 0:
#         number = abs(number)
#         # Chuyển đổi số thành dạng scientific notation
#         scientific_notation = '{:.8e}'.format(number)

#         # Tách phần nguyên và phần mũ từ scientific notation
#         integer_part, exponent_part = scientific_notation.split('e')

#         # Chuyển đổi phần nguyên thành số nguyên
#         integer_value = int(integer_part.replace('.', ''))

#         # Chuyển đổi phần mũ thành số nguyên
#         exponent = (int(exponent_part) - 8)

#         # Chuyển đổi x_value và exponent sang binary
#         x_binary_repair = bin(integer_value)[2:]  # Bỏ qua tiền tố '0b'

#         x_binary =  twos_complement( x_binary_repair)
        
#         if len(x_binary) < 32:
#             x_binary = '0' * (32 - len(x_binary)) + x_binary

#         exponent_binary = bin(exponent)[3:]  # Bỏ qua tiền tố '0b'
#         if len(exponent_binary) < 8:
#             exponent_binary = '0' * (8 - len(exponent_binary)) + exponent_binary
#         # Ghép chuỗi nhị phân của x_value và exponent lại với nhau và thêm 'b' vào đầu
#         combined_binary =x_binary + exponent_binary 


#     else:
#         # Chuyển đổi số thành dạng scientific notation
#         print(f"number: {number}")
#         print(f"number_type: {type(number)}")
#         scientific_notation = '{:.8e}'.format(number)
#         print(f"scientific_notation: {scientific_notation}")
#         print(f"scientific_notation_type: {type(scientific_notation)}")
        
#         # Tách phần nguyên và phần mũ từ scientific notation
#         integer_part, exponent_part = scientific_notation.split('e')
#         print(f"integer_part: {integer_part}")
#         print(f"exponent_part: {exponent_part}")
        
#         # Chuyển đổi phần nguyên thành số nguyên
#         integer_value = int(integer_part.replace('.', ''))
#         print(f"integer_value: {integer_value}")
        
#         # Chuyển đổi phần mũ thành số nguyên
#         exponent = (int(exponent_part) - 8)
#         print(f"exponent: {exponent}")

#         # Chuyển đổi x_value và exponent sang binary
#         x_binary = bin(integer_value)[2:]  # Bỏ qua tiền tố '0b'
#         if len(x_binary) < 32:
#             x_binary = '0' * (32 - len(x_binary)) + x_binary
            
#         exponent_binary = bin(exponent)[3:]  # Bỏ qua tiền tố '0b'
#         if len(exponent_binary) < 8:
#             exponent_binary = '0' * (8 - len(exponent_binary)) + exponent_binary

#         # Ghép chuỗi nhị phân của x_value và exponent lại với nhau và thêm 'b' vào đầu
#         combined_binary = x_binary + exponent_binary 
        
#     return combined_binary

# origin_number = 1.234

# scientific_number = convert_to_scientific_notation(origin_number)
# print(scientific_number)


# Python code to demonstrate the Exception of 
# randrange(), ValueError, start >= start
 
import tkinter as tk
from tkinter import messagebox

def on_closing():
    if messagebox.askokcancel("Quit", "Do you want to quit?"):
        top.destroy()

root = tk.Tk()
root.title("Main Window")

top = tk.Toplevel(root)
top.title("Second Window")

# Thiết lập sự kiện cho dấu 'X' đóng cửa sổ
top.protocol("WM_DELETE_WINDOW", on_closing)

root.mainloop()
 