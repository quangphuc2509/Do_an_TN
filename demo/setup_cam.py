import cv2
import numpy as np
import time

cp1 = cv2.VideoCapture(1, cv2.CAP_DSHOW)
cp1.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
cp1.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

num = 0
previous_time = time.time()

while True:
    
    ret1, frame1 = cp1.read() 
    
    now_time = time.time()
    
    if (now_time - previous_time) >= 1:
        previous_time = now_time
        cv2.imwrite('F:/DATN_HK2_2024/camera_img/img' + str(num) + '.png',frame1)
        print (f"image saved {num}")
        num = num + 1
    
    key = cv2.waitKey(1)     
    if key == 27:
        break
    
    cv2.imshow("img",frame1)
cp1.release()
cv2.destroyAllWindows()