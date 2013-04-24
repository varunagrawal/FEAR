#!/usr/bin/python

import fear
import cv
import cv2
import numpy
import os

def getGaborImages(image):

	x = cv2.imread(image)

	gabors = []

	src = gabor.preprocess(x)

	for i in range(2, 8, 2):
		for u in range(6):
			k = i
			phi = cv.CV_PI * u / 6.0
			sigma = 2* cv.CV_PI
			psi = 90

			print "%d %d" % (i, u)
			kernel = gabor.gaborKernel(src, sigma, k, phi, psi)

			h, w = src.shape
			#dst = cv.CreateMat(h, w, cv.CV_32FC1)

			dst = cv2.filter2D(src, cv.CV_32F, kernel)

			gabors.append(numpy.asarray(dst))


	for i in range(len(gabors)):
		cv2.imshow("Gabor Image", gabors[i])
		#s = "Image_%s.jpg" % i
		#cv2.imwrite(s, gabors[i])
		cv2.waitKey(0)
	
	return gabors


def show_dataset():
	root_dir = '/home/varun/Projects/FEAR/Dataset/'

	image_root = root_dir + 'cohn-kanade-images'
	landmarks_root = root_dir + 'Landmarks'

	l =  os.listdir(landmarks_root)
	level1_list = os.listdir(image_root)
	level1_list.sort()
	level1 = image_root + '/' + level1_list[0]

	level2_list = os.listdir(level1)
	level2_list.sort()
	level2 = level1 + '/' + level2_list[0]
	
	images = os.listdir(level2)
	images.sort()


	for d in level2_list:
		for i in images:
			a = cv2.imread(level2 + '/' + i)
			cv2.imshow("Dataset image", a)
			cv2.waitKey(0)
		

if __name__ == "__main__":
	#getGaborImages('../sample.jpg')
	show_dataset()
