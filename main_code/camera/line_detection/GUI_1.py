import cv2
import numpy as np
from PIL import Image, ImageTk
import tkinter as tk
from GUI_2 import *

import socket
import threading
import time
import random
import select

class First_Gui(tk.Tk):
    end_bit = 0
    def __init__(self, title, state):
        super().__init__()

        self.title(title)
        self.state(state)

        self.camera_frame = Camera_frame(self, 50, 100)
        self.working_app = working_frame(self, 50, 450)
        self.tcp_app = TCP_Protocol_Frame(self, 950, 450)
    
    def update_working_frame_main(self, camera_screen, count):
        self.working_app.update_working_frame(camera_screen, count)
        
    def send_data(self):
        if (self.tcp_app.status_send == 0):
            self.tcp_app.send_data_curve(self.camera_frame.x_curve_list, self.camera_frame.y_curve_list)
        elif (self.tcp_app.status_send == 1):
            self.tcp_app.send_data_position(self.working_app.x_point_mm, self.working_app.y_point_mm)
        self.tcp_app.update_job = self.after(5, self.send_data)
        
#========================================================================================================================================
#========================================================================================================================================
#========================================================================================================================================
                    
class Camera_frame(tk.Frame):
    def __init__(self, parent, frame_position_x, frame_position_y, frame_width = 576, frame_height = 324):
        super().__init__(parent)
        self.configure(width = frame_width + frame_width*0.7, height= frame_height)
        self.place(x = frame_position_x, y = frame_position_y)
                
        self.delay = 5
        self.frame_width = frame_width 
        self.frame_height = frame_height
        self.screen = None
        self.update_job = None
        self.update_get_value = None
        self.count = 0
        
        self.create_camera_screen(self.frame_width, self.frame_height)
        self.create_button()
        
    def create_camera_screen(self, frame_width, frame_height):
        self.canvas = tk.Canvas(self, width = frame_width, height = frame_height, bg = 'white')
        self.canvas.place(x = 0, y =0)
        
    def create_button(self):
        self.button_start = tk.Button(self, text= "Open", bg="white", font= ("Arial",13), width=15, height= 3, 
                                      cursor="hand2", activebackground= "lightgray", activeforeground= "blue", command=self.Start_camera)
        self.button_start.place(x= self.frame_width + 20, y = 50)
        
        self.button_close = tk.Button(self, text= "Close", bg="white", font= ("Arial",13), width=15, height= 3, 
                                      cursor="hand2", activebackground= "lightgray", activeforeground= "blue", command=self.Close_camera)
        self.button_close.place(x= self.frame_width + 20, y = 150)
        
        self.button_capture = tk.Button(self, text= "Capture", bg="white", font= ("Arial",13), width=15, height= 3, 
                                      cursor="hand2", activebackground= "lightgray", activeforeground= "blue", command=self.Capture)
        self.button_capture.place(x= self.frame_width + 20, y = 250)
        
        
    def Start_camera(self):
        if not self.screen or not self.screen.isOpened():
            self.screen = cv2.VideoCapture(0, cv2.CAP_DSHOW)
            self.screen.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
            self.screen.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
            self.screen.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('M', 'J', 'P', 'G'))
            # self.screen.set(cv2.CAP_PROP_FPS, 60)
            self.update()
            
    def Close_camera(self):
        if self.screen and self.screen.isOpened():
            self.screen.release()
            self.screen = None
            self.canvas.delete("all")
            if self.update_job:
                self.after_cancel(self.update_job)
                self.update_job = None
    
    def update(self):
        if self.screen and self.screen.isOpened():
            ret, self.frame = self.screen.read()
            if ret:
                self.count = self.count + 1
                self.frame_resize = cv2.resize(self.frame, (0,0), fx=0.3, fy=0.3)
                self.photo = ImageTk.PhotoImage(image= Image.fromarray(cv2.cvtColor(self.frame_resize, cv2.COLOR_BGR2RGB)))
                self.canvas.create_image(0, 0, image = self.photo, anchor = tk.NW)
                self.master.update_working_frame_main(self.frame, self.count)
                
            self.update_job = self.after(self.delay, self.update)
    
    def Capture(self):
        url = r"F:\DATN_HK2\camera_img\linearuco.jpg"
        image = cv2.imread(url)
        self.root_1 = tk.Toplevel()
        self.root_1.title("Detect Line")
        self.root_1.state("zoomed")
        # self.app = main_GUI(root=root_1, image= self.frame)
        self.app = main_GUI(root=self.root_1, image= image)
        self.root_1.protocol("WM_DELETE_WINDOW", self.on_closing)
        self.get_value()
        self.root_1.mainloop()
        
    def get_value(self):
        if hasattr(self.app, 'x_array_Perspective') and hasattr(self.app, 'y_array_Perspective'):
            self.x_curve_list = self.app.x_array_Perspective
            # print(f"self.x_curve_list:\n{self.x_curve_list}\n")
            self.y_curve_list = self.app.y_array_Perspective
            # print(f"self.y_curve_list:\n{self.y_curve_list}\n")
        self.update_get_value = self.root_1.after(self.delay, self.get_value)
    
    def on_closing(self):
        if messagebox.askokcancel("Quit", "Do you want to quit?"):
            if self.update_get_value:
                self.root_1.after_cancel(self.update_get_value)
                self.update_get_value = None
            print(f"self.x_curve_list:\n{self.x_curve_list}\n")
            print(f"self.y_curve_list:\n{self.y_curve_list}\n")
            self.root_1.destroy()

#========================================================================================================================================
#========================================================================================================================================
#========================================================================================================================================

class working_frame(tk.Frame):
    def __init__(self, parent, frame_position_x, frame_position_y, frame_width = 576, frame_height = 324):
        super().__init__(parent)
        
        self.configure(width = frame_width + frame_width*0.4, height= frame_height)
        self.place(x = frame_position_x, y = frame_position_y)
                
        self.delay = 5
        self.frame_width = frame_width
        self.frame_height = frame_height
        self.screen = None
        self.update_job = None
        self.x_point = tk.StringVar(self)
        self.y_point = tk.StringVar(self)
        self.actual_working_width = 914
        self.actual_working_height = 1502
        
        self.create_working_screen(self.frame_width, self.frame_height)
        self.create_info_label()
        self.create_info_entry()
        
    def create_working_screen(self, frame_width, frame_height):
        self.canvas = tk.Canvas(self, width = frame_width, height = frame_height, bg = 'white')
        self.canvas.place(x = 0, y =0)
        
    def update_working_frame(self, camera_screen, count):
        if camera_screen is not None:
            detection_result = detect_position(camera_screen)
            if detection_result and hasattr(detection_result, 'working_frame'):
                self.working_frame_image = detection_result.working_frame
                if self.working_frame_image is not None and self.working_frame_image.size > 0:
                    working_frame_height, working_frame_width = self.working_frame_image.shape[:2]
                    width_scale = self.actual_working_width / working_frame_width
                    height_scale = self.actual_working_height / working_frame_height
                    # self.working_frame_resize = cv2.resize(self.working_frame_image, (0,0), fx=0.3, fy=0.3)
                    self.working_frame_resize = cv2.resize(self.working_frame_image, (576,324))
                    self.working_frame_photo = ImageTk.PhotoImage(image= Image.fromarray(cv2.cvtColor(self.working_frame_resize, cv2.COLOR_BGR2RGB)))
                    self.canvas.create_image(0, 0, image = self.working_frame_photo, anchor = tk.NW)
                    if not (len(detection_result.working_coner) == 0):
                        self.x_point_mm, self.y_point_mm = self.convert_pixel_to_mm(detection_result.matrix_Perspective,
                                                                                    detection_result.working_coner[0][0],
                                                                                    detection_result.working_coner[0][1],
                                                                                    width_scale, height_scale)
                        self.update_entry(self.x_point_mm, self.y_point_mm)
                    else: 
                        self.update_entry("", "")
                    print(f"working_coner: {detection_result.working_coner}")
                    print(f"working_id: {detection_result.working_coner_ids}")
                else: 
                    self.x_point_mm = count
                    
                    self.y_point_mm = count
                    self.update_entry("", "")
            
    def create_info_label(self):
        self.x_point_label = tk.Label(self, text="Toa do x:", font= ("Arial",14))
        self.x_point_label.place(x= self.frame_width + 20, y = 50)
        self.y_point_label = tk.Label(self, text="Toa do y:", font= ("Arial",14))
        self.y_point_label.place(x= self.frame_width + 20, y = 100)
    
    def create_info_entry(self):
        self.x_point_entry = tk.Entry(self, font= ("Arial",14), width=10, textvariable= self.x_point, justify= "center")
        self.x_point_entry.place(x= self.frame_width + 110, y = 50 )
        self.y_point_entry = tk.Entry(self, font= ("Arial",14), width=10, textvariable= self.y_point, justify= "center")
        self.y_point_entry.place(x= self.frame_width + 110, y = 100 )
    
    def update_entry(self, x_point_update, y_point_update):
        self.x_point.set(str(x_point_update))
        self.y_point.set(str(y_point_update))
    
    def convert_pixel_to_mm(self, Perspective_matrix, x_point_in_pix, y_point_in_pix, x_scale, y_scale):
        Perspective_point = np.dot(Perspective_matrix, [x_point_in_pix, y_point_in_pix, 1])
        x_point_perspective, y_point_perspective, _ = Perspective_point / Perspective_point[2]
        x_point_in_mm = x_point_perspective * x_scale
        y_point_in_mm = y_point_perspective * y_scale
        return x_point_in_mm, y_point_in_mm

#========================================================================================================================================
#========================================================================================================================================
#========================================================================================================================================

class TCP_Protocol_Frame(tk.Frame):
    def __init__(self, parent, frame_position_x, frame_position_y, frame_width = 300, frame_height = 324):
        super().__init__(parent)
        
        self.FORMAT = 'utf-8'
        self.DISCONNECT_MESSAGE = "!DISCONNECT"
        self.CONNECT_MESSAGE = "HEARTBEAT"
        self.delay = 5
        self.configure(width = frame_width + frame_width*0.4, height= frame_height)
        self.place(x = frame_position_x, y = frame_position_y)
        self.server_id_variable = tk.StringVar(self)
        self.server_port_variable = tk.StringVar(self)
        self.status_tcp_sys = None
        self.status_send = None
        self.update_job = None
        self.create_label()
        self.create_entry()
        self.button_connect = self.create_button("CONNECT", self.connect, 20, 20)
        self.button_send = self.create_button("SEND", self.send_data, 20,80)
        self.button_print = self.create_button("PRINT", self.print_socket, 120, 80)
    
    def create_label(self):
        self.status_label = tk.Label(self, text="", font= ("Arial",14))
        self.status_label.place(x= 140, y = 30)
        self.sever_id_label = tk.Label(self, text="SERVER ID:", font= ("Arial",12))
        self.sever_id_label.place(x= 20, y = 150)
        self.server_port_label = tk.Label(self, text="SERVER PORT:", font= ("Arial",12))
        self.server_port_label.place(x= 20, y = 200)
        
    def create_entry(self):
        self.sever_id_entry = tk.Entry(self, font= ("Arial",14), width=15, textvariable= self.server_id_variable, justify= "center")
        self.sever_id_entry.place(x= 150, y = 150)
        self.sever_port_entry = tk.Entry(self, font= ("Arial",14), width=15, textvariable= self.server_port_variable, justify= "center")
        self.sever_port_entry.place(x= 150, y = 200)
    
    def create_button(self, text, command, x_position, y_position):
        button = tk.Button(self, text= text, bg="white", font= ("Arial",12), width=10, height= 2, 
                                      cursor="hand2", activebackground= "lightgray", activeforeground= "blue", command=command)
        button.place(x = x_position, y = y_position)
        return button
    
    def connect(self):
        self.server_port = 55555
        self.SERVER_ID = socket.gethostbyname(socket.gethostname())
        self.server_id_variable.set(str(self.SERVER_ID))
        self.server_port_variable.set(str(self.server_port))
        
        self.socket_s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Đảm bảo socket có thể tái sử dụng địa chỉ
        self.socket_s.bind((self.SERVER_ID, self.server_port))
        
        self.socket_s.listen()
        self.status_label.config(text="WAITING >>>")
        
        self.accept_thread = threading.Thread(target=self.accept_connections)
        self.accept_thread.start()
        
    def accept_connections(self):
        while True:
            try:
                self.client_socket, self.addr = self.socket_s.accept()
                print(f"self.client_socket: {self.client_socket}")
                self.status_label.config(text="READY")
                self.client_socket.send(("Ready\n").encode())
                self.client_thread = threading.Thread(target=self.handle_client, args=(self.client_socket,))
                self.client_thread.start()
            except Exception as e:
                print(f"Error accepting connections: {e}")
                break
        
    def handle_client(self, client_socket):
        # client_socket.settimeout(1.0)  # Đặt timeout cho socket
        begin_time = time.time()
        count = 0
        while True:
            try:
                ready_to_read, _, _ = select.select([client_socket], [], [], 0.1)
                # print(f"ready_to_read: {ready_to_read} lan {count}")
                # print(f"ready_to_write: {ready_to_write} lan {count}\n")
                # if ready_to_write:
                #     client_socket.send(("connected " + str(count) + "\n").encode())
                if ready_to_read:
                    mess = client_socket.recv(1024).decode()
                    # print(f"\nmess: {mess}")
                    if self.CONNECT_MESSAGE in mess:
                        current_time = time.time()
                        begin_time = current_time
                        # print(f"truong hop connect")
                    elif "DONE" in mess:
                        self.status_send = 2
                    elif mess == self.DISCONNECT_MESSAGE or not mess:
                        break
                    else: 
                        # print(f"truong hop con lai\n")
                        pass
                else:
                    current_time = time.time()
                    break_time = current_time - begin_time
                    # print(f"break time: {break_time}")
                    if(break_time > 3):
                        break
            except socket.timeout:
                # Xử lý timeout: ngắt kết nối nếu client không phản hồi trong khoảng thời gian cho phép
                print("Client connection timed out")
                break
            except ConnectionResetError:
                print("Connection was forcibly closed by the client")
                break
            except Exception as e:
                print(f"Error handling client: {e}")
                break
            
        client_socket.close()
        self.status_label.config(text= "DISCONNECTED")
        if self.update_job:
            self.after_cancel(self.master.send_data)
            self.update_job = None
        
    def print_socket(self):
        if not hasattr(self,"client_socket"):
            print(f"khong co bien client_socket")
        else:
            print(f"self.client_socket: {self.client_socket}")
            
    def send_data(self):
        self.status_send = 0
        self.master.send_data()
        
        
    def twos_complement(self, binary_str):
        # Nếu đầu vào không đủ 32 bit, bổ sung số 0 vào trước chuỗi nhị phân
        binary_str = binary_str.zfill(32)
        # Đảo bit của chuỗi nhị phân đã lọc
        reversed_binary_str = ''.join('1' if bit == '0' else '0' for bit in binary_str)
        # Cộng thêm 1
        result = bin(int(reversed_binary_str, 2) + 1)[2:]
        return result

    def convert_to_scientific_notation(self, number):
        if number < 0:
            number = abs(number)
            # Chuyển đổi số thành dạng scientific notation
            scientific_notation = '{:.8e}'.format(number)
            # Tách phần nguyên và phần mũ từ scientific notation
            integer_part, exponent_part = scientific_notation.split('e')
            # Chuyển đổi phần nguyên thành số nguyên
            integer_value = int(integer_part.replace('.', ''))
            # Chuyển đổi phần mũ thành số nguyên
            exponent = (int(exponent_part) - 8)
            # Chuyển đổi x_value và exponent sang binary
            x_binary_repair = bin(integer_value)[2:]  # Bỏ qua tiền tố '0b'
            x_binary =  self.twos_complement( x_binary_repair)
            if len(x_binary) < 32:
                x_binary = '0' * (32 - len(x_binary)) + x_binary
            exponent_binary = bin(exponent)[3:]  # Bỏ qua tiền tố '0b'
            if len(exponent_binary) < 8:
                exponent_binary = '0' * (8 - len(exponent_binary)) + exponent_binary
            # Ghép chuỗi nhị phân của x_value và exponent lại với nhau và thêm 'b' vào đầu
            combined_binary =x_binary + exponent_binary + '\n'
        else:
            # Chuyển đổi số thành dạng scientific notation
            scientific_notation = '{:.8e}'.format(number)
            # Tách phần nguyên và phần mũ từ scientific notation
            integer_part, exponent_part = scientific_notation.split('e')
            # Chuyển đổi phần nguyên thành số nguyên
            integer_value = int(integer_part.replace('.', ''))
            # Chuyển đổi phần mũ thành số nguyên
            exponent = (int(exponent_part) - 8)
            # Chuyển đổi x_value và exponent sang binary
            x_binary = bin(integer_value)[2:]  # Bỏ qua tiền tố '0b'
            if len(x_binary) < 32:
                x_binary = '0' * (32 - len(x_binary)) + x_binary
            exponent_binary = bin(exponent)[3:]  # Bỏ qua tiền tố '0b'
            if len(exponent_binary) < 8:
                exponent_binary = '0' * (8 - len(exponent_binary)) + exponent_binary
            # Ghép chuỗi nhị phân của x_value và exponent lại với nhau và thêm 'b' vào đầu
            combined_binary = x_binary + exponent_binary + '\n'
        return combined_binary
    
    def send_data_curve(self, x_position, y_position):
        # Initialize end_bit if it does not exist
        if not hasattr(self, 'end_bit'):
            self.end_bit = 0
            
        if not hasattr(self, 'end_bit_2'):
            self.end_bit_2 = 0
            
        if self.end_bit == 0:
            # print(f"x_position: {x_position}")
            for i in range(len(x_position)):
                print(f"Do_dai: {len(x_position)}")
                print(f"STT: {i}")
                x_send = self.convert_to_scientific_notation(x_position[i])
                y_send = self.convert_to_scientific_notation(y_position[i])
                # self.client_socket.send(x_send.encode())
                # self.client_socket.send(y_send.encode())
                self.client_socket.send(('x' + str(x_position[i]) + '\n').encode())
                self.client_socket.send(('y' + str(y_position[i]) + '\n').encode())
                time.sleep(0.02)
            self.end_bit = 1
            print(f"gui data curve")
        elif self.end_bit == 1:
            if self.end_bit_2 == 0:
                self.client_socket.send(('m' + str(0) + '\n').encode())
                self.client_socket.send(('n' + str(0) + '\n').encode())
                self.end_bit = 0
                self.status_send = 1
                print(f"self.tcp_app.status_send: {self.status_send}")
            
                
    def send_data_position(self, x_position, y_position):
        x_send = self.convert_to_scientific_notation(x_position)
        y_send = self.convert_to_scientific_notation(y_position)
        # self.client_socket.send(('x' + str(x_position) + '\n').encode())
        # self.client_socket.send(('y' + str(y_position) + '\n').encode())
        print(f"gui data_position")
        
if __name__ == "__main__":
    app = First_Gui("man hinh chinh", "zoomed")
    
    app.mainloop()