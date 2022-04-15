import cv2 as cv

def testDevice(source):
	cap = cv.VideoCapture(source)
	if cap is None or not cap.isOpened():
       		print('Warning: unable to open video source: ', source)
	else:
       		print('Le source is: ',source);

#why they did this I have no idea
testDevice(14)
for i in range(16):
	testDevice(i)
