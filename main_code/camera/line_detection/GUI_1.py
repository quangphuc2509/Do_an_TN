import cv2
import numpy as np
from PIL import Image, ImageTk
import tkinter as tk
from GUI_2 import *

class First_Gui(tk.Tk):
    def __init__(self, title, state):
        super().__init__()

        self.title(title)
        self.state(state)

        self.camera_frame = Camera_frame(self, 30, 100)
        self.working_app = working_frame(self, 30, 450)
    
    def update_working_frame(self, camera_screen):
        if camera_screen is not None:
            detection_result = detect_position(camera_screen)
            if detection_result and hasattr(detection_result, 'working_frame'):
                self.working_frame_image = detection_result.working_frame
                if self.working_frame_image is not None and self.working_frame_image.size > 0:
                    working_frame_height, working_frame_width = self.working_frame_image.shape[:2]
                    # self.working_frame_resize = cv2.resize(self.working_frame_image, (0,0), fx=0.3, fy=0.3)
                    self.working_frame_resize = cv2.resize(self.working_frame_image, (576,324))
                    self.working_frame_photo = ImageTk.PhotoImage(image= Image.fromarray(cv2.cvtColor(self.working_frame_resize, cv2.COLOR_BGR2RGB)))
                    self.working_app.canvas.create_image(0, 0, image = self.working_frame_photo, anchor = tk.NW)
                    # print(f"working_coner: {detection_result.working_coner}")
                    # print(f"working_id: {detection_result.working_coner_ids}")
                    
class Camera_frame(tk.Frame):
    def __init__(self, parent, frame_position_x, frame_position_y, frame_width = 576, frame_height = 324):
        super().__init__(parent)
        self.configure(width = frame_width + frame_width*0.4, height= frame_height)
        self.place(x = frame_position_x, y = frame_position_y)
                
        self.delay = 5
        self.frame_width = frame_width 
        self.frame_height = frame_height
        self.screen = None
        self.update_job = None
        
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
            self.screen = cv2.VideoCapture(1, cv2.CAP_DSHOW)
            self.screen.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
            self.screen.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
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
                self.frame_resize = cv2.resize(self.frame, (0,0), fx=0.3, fy=0.3)
                self.photo = ImageTk.PhotoImage(image= Image.fromarray(cv2.cvtColor(self.frame_resize, cv2.COLOR_BGR2RGB)))
                self.canvas.create_image(0, 0, image = self.photo, anchor = tk.NW)
                self.master.update_working_frame(self.frame)
            self.update_job = self.after(self.delay, self.update)
    
    def Capture(self):
        root_1 = tk.Toplevel()
        root_1.title("Detect Line")
        root_1.state("zoomed")
        app = main_GUI(root=root_1, image= self.frame)
        root_1.mainloop()

#========================================================================================================================================
#========================================================================================================================================
#========================================================================================================================================

class working_frame(tk.Frame):
    def __init__(self, parent, frame_position_x, frame_position_y, frame_width = 576, frame_height = 324):
        super().__init__(parent)
        
        self.configure(width = frame_width + frame_width*0.4, height= frame_height)
        self.place(x = frame_position_x, y = frame_position_y)
                
        self.delay = 15
        self.frame_width = frame_width
        self.frame_height = frame_height
        self.screen = None
        self.update_job = None
        self.create_working_screen(self.frame_width, self.frame_height)
        
        
    def create_working_screen(self, frame_width, frame_height):
        self.canvas = tk.Canvas(self, width = frame_width, height = frame_height, bg = 'white')
        self.canvas.place(x = 0, y =0)
        
    
    
        
if __name__ == "__main__":
    app = First_Gui("man hinh chinh", "zoomed")
    app.mainloop()