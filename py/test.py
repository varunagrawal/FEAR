#!/usr/bin/python

import fear
import utils
import cv2
import numpy
import mlpy
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


	"""for i in range(len(gabors)):
		cv2.imshow("Gabor Image", gabors[i])
		#s = "Image_%s.jpg" % i
		#cv2.imwrite(s, gabors[i])
		cv2.waitKey(0)"""
	
	return gabors


def show_dataset():
	
	root_dir = '/home/varun/Projects/FEAR/Dataset/'

	image_root = root_dir + 'cohn-kanade-images'
	landmarks_root = root_dir + 'Landmarks'

	image1_list = os.listdir(image_root)
	image1_list.sort()
	landmark1_list = os.listdir(landmarks_root)
	landmark1_list.sort()

	print len(image1_list)
	
	for f1 in image1_list[:-5]:
		image1 = image_root + '/' + f1
		landmark1 = landmarks_root + '/' + f1

		image2_list = os.listdir(image1)
		image2_list.sort()

		landmark2_list = os.listdir(landmark1)
		landmark2_list.sort()
		
		for f2 in image2_list[]:
				image2 = image1 + '/' + f2
				landmark2 = landmark1 + '/' + f2

				images = os.listdir(image2)
				images.sort()
				
				landmarks = os.listdir(landmark2)
				landmarks.sort()


				for i in range(len(images)):
						image_file = image2 + '/' + images[i]
						landmark_file = landmark2 + '/' + landmarks[i]

						print "File: %s" % image_file
			
						points = utils.getPoints(landmark_file)

						for x, y in points:
								utils.mark(image_file, x, y)
		

if __name__ == "__main__":
	#getGaborImages('../sample.jpg')
	show_dataset()
