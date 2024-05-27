import cv2
import numpy as np
from PIL import Image, ImageTk
import tkinter as tk
from detection_line import *
from tkinter import messagebox
from Detection_robot import *

class ImageResizerApp:
    def __init__(self, canvas, image):
        self.canvas = canvas
        
        # Load image using OpenCV
        self.cv_image = image
        self.cv_image = cv2.cvtColor(self.cv_image, cv2.COLOR_BGR2RGB)
        self.image_height, self.image_width = self.cv_image.shape[:2]

        # Convert image to PIL format
        self.image = Image.fromarray(self.cv_image)
        self.photo = ImageTk.PhotoImage(self.image)

        # Display the image on the canvas
        self.image_item = self.canvas.create_image(0, 0, anchor=tk.NW, image=self.photo)

        # Bind mouse events to functions
        self.canvas.bind("<MouseWheel>", self.resize_image)
        self.canvas.bind("<Motion>", self.update_mouse_position)
        self.canvas.bind("<ButtonPress-1>", self.start_pan)
        self.canvas.bind("<B1-Motion>", self.pan_image)
        self.canvas.bind("<Button-3>", self.show_coordinates)

        # Initial state variables
        self.scale = 1.0
        self.offset_x = 0
        self.offset_y = 0
        self.mouse_x = 0
        self.mouse_y = 0
        self.pan_start_x = 0
        self.pan_start_y = 0

    def update_mouse_position(self, event):
        self.mouse_x = event.x
        self.mouse_y = event.y

    def start_pan(self, event):
        self.pan_start_x = event.x
        self.pan_start_y = event.y

    def pan_image(self, event):
        dx = event.x - self.pan_start_x
        dy = event.y - self.pan_start_y
        self.offset_x = min(max(self.offset_x - dx, 0), int(self.image_width * self.scale) - self.canvas.winfo_width())
        self.offset_y = min(max(self.offset_y - dy, 0), int(self.image_height * self.scale) - self.canvas.winfo_height())
        self.pan_start_x = event.x
        self.pan_start_y = event.y
        self.redraw_image()

    def resize_image(self, event):
        # Change scale factor based on scroll direction
        if event.delta > 0:
            self.scale += 0.05
        else:
            self.scale -= 0.05

        # Ensure scale is within bounds
        self.scale = max(0.1, min(self.scale, 10.0))

        # Adjust offsets to keep image centered
        self.offset_x = 0
        self.offset_y = 0

        # Redraw the image with new scale
        self.redraw_image()
    
    def redraw_image(self):
        # Calculate new dimensions
        new_width = int(self.image_width * self.scale)
        new_height = int(self.image_height * self.scale)

        # Resize the image
        resized_cv_image = cv2.resize(self.cv_image, (new_width, new_height))

        # Calculate the region to display based on current offsets
        end_x = min(self.offset_x + self.canvas.winfo_width(), new_width)
        end_y = min(self.offset_y + self.canvas.winfo_height(), new_height)
        cropped_cv_image = resized_cv_image[self.offset_y:end_y, self.offset_x:end_x]

        # Convert resized and cropped image to PIL format and update the canvas
        resized_image = Image.fromarray(cropped_cv_image)
        self.photo = ImageTk.PhotoImage(resized_image)
        self.canvas.create_image(0, 0, anchor=tk.NW, image=self.photo)

    def show_coordinates(self, event):
        # Calculate the actual coordinates on the original image
        self.actual_x = int((self.offset_x + event.x) / self.scale)
        self.actual_y = int((self.offset_y + event.y) / self.scale)
        print(f"Mouse coordinates on image: ({self.actual_x}, {self.actual_y})")
        
        
class main_GUI(Detection_line):
    def __init__(self, root, image, blured_value = 5):
        super().__init__(image, blured_value)
        self.root = root
        self.image = image
        self.image_clean = copy.deepcopy(self.image)
        
        self.dectect_position = detect_position(self.image)
        Detection_line.__init__(self,image=self.dectect_position.working_frame, blured_value = 5)
        canvas_width = 350
        canvas_height = 500
        x_canvas = 50
        y_canvas = 10
        
        # actual_width = 300
        # actual_height = 178
        
        self.actual_width = 210
        self.actual_height = 297
        
        # Create a canvas to display the image
        self.canvas_1 = tk.Canvas(root, width=canvas_width, height=canvas_height, bg='white')
        self.canvas_1.place(x=x_canvas, y = y_canvas)
        self.canvas_2 = tk.Canvas(root, width=canvas_width, height=canvas_height, bg='white')
        self.canvas_2.place(x=x_canvas + canvas_width + 10, y = y_canvas)
        self.canvas_3 = tk.Canvas(root, width=canvas_width, height=canvas_height, bg='white')
        self.canvas_3.place(x=x_canvas + (canvas_width + 10)*2, y = y_canvas)
        self.canvas_4 = tk.Canvas(root, width=canvas_width, height=canvas_height, bg='white')
        self.canvas_4.place(x=x_canvas + (canvas_width + 10)*3, y = y_canvas)
        
        self.app1 = ImageResizerApp(self.canvas_1, self.image_clean)
        self.app2 = ImageResizerApp(self.canvas_2, self.dectect_position.working_frame)
        self.app3 = ImageResizerApp(self.canvas_3, self.edges_image)
        # self.app4 = ImageResizerApp(canvas_4, self.image)
        
        # print(f"matrix: \n{self.dectect_position.matrix_Perspective}")
        # print(f"inverse matrix: \n{self.dectect_position.inverse_matrix_Perspective}")
        
        self.working_height, self.working_width = self.dectect_position.working_frame.shape[:2]
        # print(f"working_height: {self.working_height}\nworking_width: {self.working_width}")
        
        self.scale_height = self.actual_height / self.working_height
        self.scale_width = self.actual_width / self.working_width
        
        self.app1.actual_x = None
        self.app1.actual_y = None
        self.app2.actual_x = None
        self.app2.actual_y = None
        
        # print(f"sacle_height: {self.scale_height}\scale_width: {self.scale_width}")

        
        # Create a track bar (Scale) to adjust image scale
        self.scale_var = tk.DoubleVar(value = blured_value)
        self.scale_bar = tk.Scale(self.root, from_=1, to=10, resolution=2, orient=tk.HORIZONTAL, label="Scale", 
                                  variable=self.scale_var, command=self.update_blured_value, width=15, length=200)
        self.scale_bar.place(x=50, y=canvas_height+ 30)
        
        self.button_curve = tk.Button(master= self.root, text = "curve", bg="white", font= ("Arial",13), command = self.update_curves_image,
                                      width=15, height= 3, cursor="hand2", activebackground= "lightgray", activeforeground= "blue")
        self.button_curve.place(x = x_canvas + (canvas_width + 10)*3, y = canvas_height+ 30)
        
        self.button_calc = tk.Button(master= self.root, text = "calculation", bg="white", font= ("Arial",13), command = self.calc_Perspective_point,
                                      width=15, height= 3, cursor="hand2", activebackground= "lightgray", activeforeground= "blue")
        self.button_calc.place(x = x_canvas + canvas_width + 10, y = canvas_height+ 30)
        
        self.button_calc = tk.Button(master= self.root, text = "calculation", bg="white", font= ("Arial",13), command = self.calc_Perspective_point,
                                      width=15, height= 3, cursor="hand2", activebackground= "lightgray", activeforeground= "blue")
        self.button_calc.place(x = x_canvas + canvas_width + 10, y = canvas_height+ 30)
        self.button_calc_1 = tk.Button(master= self.root, text = "calculation_1", bg="white", font= ("Arial",13), command = self.Calc_first_point,
                                      width=15, height= 3, cursor="hand2", activebackground= "lightgray", activeforeground= "blue")
        self.button_calc_1.place(x = x_canvas + (canvas_width + 10)*2, y = canvas_height+ 30)
        
    def update_blured_value(self, value):
        self.blured_value = int(value)
        self.update_edges_image()
        self.app3.cv_image = self.edges_image
        self.app3.redraw_image()

    def update_edges_image(self):
        self.blured_image = cv2.GaussianBlur(self.gray_image, (self.blured_value, self.blured_value), 0)
        self.edges_image = cv2.Canny(self.blured_image, 80, 210, apertureSize=3)
        
    def calc_Perspective_point(self):
        
        if (self.app1.actual_x) and (self.app1.actual_y):
            self.Perspective_point = np.dot(self.dectect_position.matrix_Perspective, [self.app1.actual_x, self.app1.actual_y, 1])
            self.x_Perspective_point, self. y_Perspective_point, _ = self.Perspective_point / self.Perspective_point[2]
            print(f"Perspective_point: ({int(self.x_Perspective_point)}, {int(self. y_Perspective_point)})")
            print(f"Perspective_point: ({self.x_Perspective_point:.4f}, {self. y_Perspective_point:.4f})")
            self.actual_x_calc = self.x_Perspective_point * self.scale_width
            self.actual_y_calc = self.y_Perspective_point * self.scale_height
            print(f"Perspective_point_mm: ({self.actual_x_calc:.4f}, {self. actual_y_calc:.4f})")
        else:
            msg = messagebox.showinfo("warning", "chua co gia tri")
    
    def update_curves_image(self):
        self.cureves_perform(self.app2.actual_x, self.app2.actual_y)
        self.canvas_4.delete("all")
        self.app4 = ImageResizerApp(self.canvas_4, self.curves_image)
        self.app4.cv_image = self.curves_image
        self.app4.redraw_image()
        self.working_height, self.working_width = self.curves_image.shape[:2]
        # print(f"working_height: {self.working_height}\nworking_width: {self.working_width}")
        self.scale_height = self.actual_height / self.working_height
        self.scale_width = self.actual_width / self.working_width
        # print(f"sacle_height: {self.scale_height}\scale_width: {self.scale_width}")
        # print(f"self.average_points_filted:\n{self.average_points_filted[0][0]}")
        
        # self.x_array_to_Perspective = np.array(self.x_list_to_Perspective)
        # self.y_array_to_Perspective = np.array(self.y_list_to_Perspective)
        # self.x_array_Perspective = self.x_array_to_Perspective * self.scale_width
        # self.y_array_Perspective = self.y_array_to_Perspective * self.scale_height
        self.x_array_Perspective = [element * self.scale_width for element in self.x_list_to_Perspective]
        self.y_array_Perspective = [element * self.scale_height for element in self.y_list_to_Perspective]
        # print(f"x_array_Perspective:\n{self.x_array_Perspective}")
        # print(f"y_array_Perspective:\n{self.y_array_Perspective}")
    
    def Calc_first_point(self):
        if (self.app2.actual_x is not None)  and (self.app2.actual_y is not None):
            self.x_first_list, self.y_first_list = self.first_boundary_separation(self.app2.actual_x, self.app2.actual_y)
            print(f"self.x_first_list:\n{self.x_first_list}")
            print(f"self.y_first_list:\n{self.y_first_list}")
        else:
            msg = messagebox.showinfo("warning", "chua co gia tri")
        
if __name__ == "__main__":
    root = tk.Tk()
    root.title("Image Resizer with Fixed Frame")
    root.state('zoomed')
    
    url = r"F:\DATN_HK2\camera_img\linearuco.jpg"
    image = cv2.imread(url)
    app = main_GUI(root, image)
    root.mainloop()
