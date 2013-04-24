# Module for FEAR utility functions functions
# Author: Varun Agrawal

import cv
import cv2
import numpy
import math


# Locate face in image. Using cv2 functions
def detect_face(image):

	#Init the classifier
	face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml"
	
	face_cascade = cv2.CascadeClassifier()
	face_cascade.load(face_cascade_name)

	#Preprocess the image
	grayimg = cv2.cvtColor(image, cv.CV_BGR2GRAY)
	grayimg = cv2.equalizeHist(grayimg)
	
	#Run the classifiers
	faces = face_cascade.detectMultiScale(grayimg, 1.1, 2, 0|cv.CV_HAAR_SCALE_IMAGE, (30, 30))
	
	print "Faces detected"
	
	if len(faces) != 0:
		for face in faces:
			cv2.rectangle(image, (face[0], face[1]),
					  (face[0]+face[2], face[1]+face[3]), cv.RGB(155, 255, 25), 2)

	cv2.imshow("Detected face", image)
	cv2.waitKey(0)


	
# Preprocess image for filtering
def preprocess(img):
	
	height, width, channels = img.shape
	out_f = cv.CreateMat(height, width, cv.CV_32FC1)

	#Convert from RGB to Grayscale
	out = cv2.cvtColor(img, cv.CV_BGR2GRAY)
	#Change the datatype
	out_f = numpy.float32(out)
	#scale the output
	out_f = out * (1.0/255) 

	#cv.ConvertScale(cv.fromarray(out), out_f, 1.0/255, 0); #Same as convertTo since we just need to scale
	#return numpy.asarray(out_f)
	
	return out_f


# Returns a Gabor kernel for an image
def gaborKernel( img, sigma, kv, phi, psi ):

	src = cv.fromarray(img)
	kernel = numpy.zeros(img.shape)

	hwidth = (src.cols - 1) / 2
	hheight = (src.rows - 1) / 2


	sigma = sigma / 10.0
	kv = kv / 10.0
	phi = phi
	psi = cv.CV_PI * psi / 180.0

	for y in range(-hheight, hheight+1):
		for x in range(-hwidth, hwidth+1):
			val = math.exp( -((x*x) + (y*y)) / (2*sigma*sigma) ) * math.cos( kv*x*math.cos(phi) + kv*y*math.sin(phi) + psi)
			kernel[hheight + y][hwidth + x] = val

			
	return kernel
	


if __name__ == "__main__":
	img = cv2.imread('../msit.jpg')
	detect_face(img)
	#out = preprocess(img)
	#cv2.imshow("Test", out)
	#cv.WaitKey(0)
