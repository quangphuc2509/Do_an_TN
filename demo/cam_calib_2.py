import base64
import os
import time
import numpy as np
import cv2
import time
from numpy import savetxt
from numpy import genfromtxt

checkerboard = (7,9)
Min_points = 50
Record = True

# Dừng vòng lặp khi đã đạt đến độ chính xác nhất định hoặc hoàn thành số lần lặp được chỉ định
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# vector chứa các điểm 3D
threepoints = []

# vector chứa các điểm 2D
twopoints = []

# Điểm 3D hệ tọa độ thực
object3d = np.zeros((1, checkerboard[0]*checkerboard[1], 3), np.float32)
object3d[0, :, :2] = np.mgrid[0: checkerboard[0], 0: checkerboard[1]].T.reshape(-1, 2)
prev_img_shape = None

cap = cv2.VideoCapture(1, cv2.CAP_DSHOW)
FPS = cap.get(cv2.CAP_PROP_FPS)

# kiểm tra webcam có hoạt động không
if not cap.isOpened():
    raise IOError("Cannot open webcam")

if Record:
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    writer = cv2.VideoWriter('calibration.mp4', cv2.VideoWriter_fourcc(*'DIVX'), FPS, (width, height))

while True:
    ret, img = cap.read()
    image = img
    grayColor = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    # Tìm góc của bàn cờ
    # Nếu phát hiện số góc mong muốn trên bàn cờ thì ret = true
    ret, corners = cv2.findChessboardCorners(grayColor, checkerboard, cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_FAST_CHECK + cv2.CALIB_CB_NORMALIZE_IMAGE)
    
    if ret == True:
        threepoints.append(object3d)
        
        corners2 = cv2.cornerSubPix(grayColor, corners, checkerboard, (-1, -1), criteria)
        
        twopoints.append(corners2)
        
        if len(twopoints) > Min_points:
            cap.release()
            if Record: writer.release()
            cv2.destroyAllWindows()
            break
        
        image = cv2.drawChessboardCorners(image, checkerboard, corners2, ret)
    
    cv2.imshow('img', image)
    
    if Record:
        writer.write(image)
    
    k = cv2.waitKey(1)
    if k == 27:
        cap.release()
        if Record: writer.release()
        cv2.destroyAllWindows()
        break
    
    h, w = image.shape[:2] 
 
# Perform camera calibration by
# passing the value of above found out 3D points (threedpoints)
# and its corresponding pixel coordinates of the
# detected corners (twodpoints):
ret, matrix, distortion, r_vecs, t_vecs = cv2.calibrateCamera(threepoints, twopoints, grayColor.shape[::-1], None, None) 
 
# Displaying required output
print(" Camera matrix:")
print(matrix)
 
print("\n Distortion coefficient:")
print(distortion)
 
print("\n Rotation Vectors:")
print(r_vecs)
 
print("\n Translation Vectors:")
print(t_vecs)

mean_r = np.mean(np.asarray(r_vecs), axis=0)
mean_t = np.mean(np.asarray(t_vecs), axis=0)
savetxt('rotation_vectors.csv', mean_r, delimiter=',')
savetxt('translation_vectors.csv', mean_t, delimiter=',')
savetxt('camera_matrix.csv', matrix, delimiter=',')
savetxt('camera_distortion.csv', distortion, delimiter=',')