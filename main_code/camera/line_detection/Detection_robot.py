# file này chứa chương trình thực hiện xác định vị trí của robot theo mm
import cv2
import time
import numpy as np
from detect_marker import *
import matplotlib.pyplot as plt
import copy

class detect_position():
    def __init__(self, image):
        
        self.ARUCO_DICT = {
            "DICT_4X4_50": cv2.aruco.DICT_4X4_50,
            "DICT_4X4_100": cv2.aruco.DICT_4X4_100,
            "DICT_4X4_250": cv2.aruco.DICT_4X4_250,
            "DICT_4X4_1000": cv2.aruco.DICT_4X4_1000,
            "DICT_5X5_50": cv2.aruco.DICT_5X5_50,
            "DICT_5X5_100": cv2.aruco.DICT_5X5_100,
            "DICT_5X5_250": cv2.aruco.DICT_5X5_250,
            "DICT_5X5_1000": cv2.aruco.DICT_5X5_1000,
            "DICT_6X6_50": cv2.aruco.DICT_6X6_50,
            "DICT_6X6_100": cv2.aruco.DICT_6X6_100,
            "DICT_6X6_250": cv2.aruco.DICT_6X6_250,
            "DICT_6X6_1000": cv2.aruco.DICT_6X6_1000,
            "DICT_7X7_50": cv2.aruco.DICT_7X7_50,
            "DICT_7X7_100": cv2.aruco.DICT_7X7_100,
            "DICT_7X7_250": cv2.aruco.DICT_7X7_250,
            "DICT_7X7_1000": cv2.aruco.DICT_7X7_1000,
            "DICT_ARUCO_ORIGINAL": cv2.aruco.DICT_ARUCO_ORIGINAL,
            "DICT_APRILTAG_16h5": cv2.aruco.DICT_APRILTAG_16h5,
            "DICT_APRILTAG_25h9": cv2.aruco.DICT_APRILTAG_25h9,
            "DICT_APRILTAG_36h10": cv2.aruco.DICT_APRILTAG_36h10,
            "DICT_APRILTAG_36h11": cv2.aruco.DICT_APRILTAG_36h11
        }

        self.aruco_type = "DICT_ARUCO_ORIGINAL"
        self.aruco_dict = cv2.aruco.getPredefinedDictionary(self.ARUCO_DICT[self.aruco_type])
        self.aruco_para = cv2.aruco.DetectorParameters()
        
        self.frame = copy.deepcopy(image)
        self.frame_clean = copy.deepcopy(image)
        self.working_corner = []
        
        self.update_detect_marker()
        
    def update_detect_marker(self):
        self.marker_corners, self.id_list = Get_markers(self.frame, aruco_dict= self.aruco_dict, aruco_para= self.aruco_para)
        print(f"self.marker_corners: \n{self.marker_corners}")
        draw_marker(self.frame, self.marker_corners, self.id_list)
        
        self.center_markers_point = get_Marker_Center_Coordinate(self.marker_corners)
        
        self.frame_with_square, self.square_found = draw_field(self.frame, self.center_markers_point, self.id_list)
        
        if self.square_found:
            self.working_corner = self.center_markers_point
        
        if self.working_corner:
            self.matrix_Perspective, self.working_frame = four_point_transform(self.frame_clean, np.array(self.working_corner))
        # self.inverse_matrix_Perspective = np.linalg.inv(self.matrix_Perspective)
    def position_extraction(self):
        
        pass