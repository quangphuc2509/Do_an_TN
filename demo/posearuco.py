import numpy as np
import cv2
import sys
import time
import math


ARUCO_DICT = {
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

def aruco_display(corners, ids, rejected, image):
    
	if len(corners) > 0:
		
		ids = ids.flatten()
		
		for (markerCorner, markerID) in zip(corners, ids):
			
			corners = markerCorner.reshape((4, 2))
			(topLeft, topRight, bottomRight, bottomLeft) = corners
			
			topRight = (int(topRight[0]), int(topRight[1]))
			bottomRight = (int(bottomRight[0]), int(bottomRight[1]))
			bottomLeft = (int(bottomLeft[0]), int(bottomLeft[1]))
			topLeft = (int(topLeft[0]), int(topLeft[1]))

			cv2.line(image, topLeft, topRight, (0, 255, 0), 2)
			cv2.line(image, topRight, bottomRight, (0, 255, 0), 2)
			cv2.line(image, bottomRight, bottomLeft, (0, 255, 0), 2)
			cv2.line(image, bottomLeft, topLeft, (0, 255, 0), 2)
			
			cX = int((topLeft[0] + bottomRight[0]) / 2.0)
			cY = int((topLeft[1] + bottomRight[1]) / 2.0)
			cv2.circle(image, (cX, cY), 4, (0, 0, 255), -1)
			
			cv2.putText(image, str(markerID),(topLeft[0], topLeft[1] - 10), cv2.FONT_HERSHEY_SIMPLEX,
				0.5, (0, 255, 0), 2)
			print("[Inference] ArUco marker ID: {}".format(markerID))
			
	return image



def pose_estimation(frame, aruco_dict_type, matrix_coefficients, distortion_coefficients):
    
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.aruco_dict = cv2.aruco.getPredefinedDictionary(aruco_dict_type)
    parameters = cv2.aruco.DetectorParameters()

    corners, ids, rejected_img_points = cv2.aruco.detectMarkers(gray, cv2.aruco_dict,parameters=parameters)

    if len(corners) > 0:
        rvecs, tvecs, markerPoints = cv2.aruco.estimatePoseSingleMarkers(corners, 0.042, matrix_coefficients, distortion_coefficients)
        
        # for i in range(len(ids)):
        #     # rvecs, tvecs, markerPoints = cv2.aruco.estimatePoseSingleMarkers(corners[i], 0.032, matrix_coefficients, distortion_coefficients)
        #     rvec, tvec = rvecs[i], tvecs[i]
        #     marker_pos_3d = np.array([tvec[0][0], tvec[0][1], tvec[0][2]])
        #     distance = np.linalg.norm(marker_pos_3d)
        #     print(f"tvec 2: {tvec[0][2]}")
        #     # print(".............cap nhat................")
        #     cv2.putText(frame, f"distance: {(tvec[0][2]*1000):.2f} mm", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        #     cv2.aruco.drawDetectedMarkers(frame, corners)
        #     cv2.drawFrameAxes(frame, matrix_coefficients, distortion_coefficients, rvec, tvec, 0.01)
        
        # Tính toán khoảng cách giữa các mã Aruco
        for i in range(len(ids)):
            rvec, tvec = rvecs[i], tvecs[i]
            for j in range(i+1, len(ids)):
            
                marker1_pos = np.array([tvecs[i][0][0], tvecs[i][0][1], tvecs[i][0][2]])
                marker2_pos = np.array([tvecs[j][0][0], tvecs[j][0][1], tvecs[j][0][2]])
                print(f"marker 1: {tvecs[i][0]}")
                print(f"marker 2: {tvecs[j][0]}")
                distance_between_markers = np.linalg.norm(marker1_pos - marker2_pos)
                # Hiển thị khoảng cách giữa các mã Aruco
                cv2.putText(frame, f"Distance between {ids[i]} and {ids[j]}: {(distance_between_markers*1000):.2f} units", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                cv2.aruco.drawDetectedMarkers(frame, corners)
            cv2.drawFrameAxes(frame, matrix_coefficients, distortion_coefficients, rvec, tvec, 0.01)
                
    return frame


    

aruco_type = "DICT_ARUCO_ORIGINAL"

arucoDict = cv2.aruco.getPredefinedDictionary(ARUCO_DICT[aruco_type])

arucoParams = cv2.aruco.DetectorParameters()


# intrinsic_camera = np.array(((933.15867, 0, 657.59),(0,933.1586, 400.36993),(0,0,1)))
# distortion = np.array((-0.43948,0.18514,0,0)qq)

# intrinsic_camera = np.array(((1.14870557e+03, 0, 3.87448025e+02),(0, 1.13926358e+03, 1.79631597e+02),(0,0,1)))
# distortion = np.array((0.74215192, 2.42698929, -0.04479061, 0.05172736, -24.76919683))

# intrinsic_camera = np.array(((754.44365924, 0, 624.89657487),(0, 753.9295624, 371.71309098),(0,0,1)))
# distortion = np.array((0.2047615, -0.52777265, -0.00077147, -0.0012213, 0.35767539))

intrinsic_camera = np.array(((748.6428912, 0, 621.47894117),(0, 747.27478157, 385.86509944),(0,0,1)))
distortion = np.array(( 0.22713412, -0.68075899, 0.00772914, -0.00151355, 0.73952917))

# intrinsic_camera = np.array(((741.01221574, 0, 619.97157395),(0, 740.66292304, 382.66205804),(0,0,1)))
# distortion = np.array(( 0.20449226, -0.50249379, 0.00464502, -0.00270931, 0.30470497))

# intrinsic_camera = np.array(((1000.44365924, 0, 624.89657487),(0, 1000.9295624, 371.71309098),(0,0,1)))
# distortion = np.array((0.2047615, -0.52777265, -0.00077147, -0.0012213, 0.35767539))

cap = cv2.VideoCapture(1, cv2.CAP_DSHOW)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

begin_time = time.time()


while cap.isOpened():
    
    ret, img = cap.read()
    
    output = pose_estimation(img, ARUCO_DICT[aruco_type], intrinsic_camera, distortion)

    cv2.imshow('Estimated Pose', output)

    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()