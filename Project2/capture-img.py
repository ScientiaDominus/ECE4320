import numpy as np
import cv2
import time


print("Press enter to start the process >> ")
input()

CamL_id = 0
CamR_id = 2



CamL= cv2.VideoCapture(CamL_id, cv2.CAP_V4L)
CamR= cv2.VideoCapture(CamR_id, cv2.CAP_V4L)
output_path = "./data/"

start = time.time()
T = 6
count = 0

while True:
    timer = T - int(time.time() - start)
    retR, frameR= CamR.read()
    retL, frameL= CamL.read()
    
    img1_temp = frameL.copy()
    cv2.putText(img1_temp,"%r"%timer,(50,50),1,5,(55,0,0),5)
    cv2.imshow('imgR',frameR)
    cv2.imshow('imgL',img1_temp)

    grayR= cv2.cvtColor(frameR,cv2.COLOR_BGR2GRAY)
    grayL= cv2.cvtColor(frameL,cv2.COLOR_BGR2GRAY)

    # Find the chess board corners
    retR, cornersR = cv2.findChessboardCorners(grayR,(9,6),None)
    retL, cornersL = cv2.findChessboardCorners(grayL,(9,6),None)

    # If corners are detected in left and right image then we save it.
    if (retR == True) and (retL == True) and timer <=0:
        count+=1
        cv2.imwrite(output_path+'stereoR/img%d.png'%count,frameR)
        cv2.imwrite(output_path+'stereoL/img%d.png'%count,frameL)
        print("saved frame: ", count)
    
    if timer <=0:
        start = time.time()
    
    # Press esc to exit
    if cv2.waitKey(1) & 0xFF == 27:
        print("Closing the cameras!")
        break

# Release the Cameras
CamR.release()
CamL.release()
cv2.destroyAllWindows()
