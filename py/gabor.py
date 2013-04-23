# Module for Gabor Kernel functions
# Author: Varun Agrawal

import cv
import cv2
import numpy
import math

def preprocess(img):
	
	height, width, channels = img.shape
	out_f = cv.CreateMat(height, width, cv.CV_32FC1)

	out = cv2.cvtColor(img, cv.CV_BGR2GRAY)
	out_f = numpy.float32(out)
	out_f = out * (1.0/255)
	#cv.ConvertScale(cv.fromarray(out), out_f, 1.0/255, 0); #Same as convertTo since we just need to scale

	#return numpy.asarray(out_f)
	return out_f


def gaborKernel( src, sigma, kv, phi, psi ):

	src = cv.fromarray(src)
	kernel = cv.CreateMat(src.rows, src.cols, src.type)

	hwidth = (src.cols - 1) / 2
	hheight = (src.rows - 1) / 2


	sigma = sigma / 10.0
	kv = kv / 10.0
	phi = phi
	psi = cv.CV_PI * psi / 180.0

	for y in range(-hheight, hheight):
		for x in range(-hwidth, hwidth):
			val = math.exp( -((x*x) + (y*y)) / (2*sigma*sigma) ) * math.cos( kv*x*math.cos(phi) + kv*y*math.sin(phi) + psi)
			cv.Set2D(kernel, hheight + y, hwidth + x, cv.Scalar(val))

			
	return kernel



if __name__ == "__main__":
	img = cv2.imread('../sample.jpg')
	out = preprocess(img)
	cv2.imshow("Test", out)
	cv.WaitKey(0)
