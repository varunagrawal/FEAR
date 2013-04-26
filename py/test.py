#!/usr/bin/python

import fear
import utils
import cv2
import cv
import numpy
import mlpy
import os


def show_dataset():
	
	root_dir = '/home/varun/Projects/FEAR/Dataset/'

	image_root = root_dir + 'cohn-kanade-images'
	landmarks_root = root_dir + 'Landmarks'

	image1_list = os.listdir(image_root)
	image1_list.sort()
	landmark1_list = os.listdir(landmarks_root)
	landmark1_list.sort()

	#print len(image1_list)
	
	for f1 in image1_list[:1]:
		image1 = image_root + '/' + f1
		landmark1 = landmarks_root + '/' + f1

		image2_list = os.listdir(image1)
		image2_list.sort()

		landmark2_list = os.listdir(landmark1)
		landmark2_list.sort()
		
		for f2 in image2_list:
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
						
						gabors = fear.getGaborImages(image_file)
						trainSVMs(gabors, points)

						#for x, y in points:
						#		utils.mark(image_file, x, y)



def packGaborImages(gabors):

	for g in gabors:
		g.resize(g.size, 1)

	x = gabors[0]
		
	for i in range(1, len(gabors)):
		x = numpy.hstack((x, gabors[i]))

	return x

	
						
# Train SVMs to detect feature points. Input: List of Gabor images and array of feature point locations
def trainSVMs(gabors, points):
		
	svm = mlpy.LibSvm( svm_type='c_svc', kernel_type='rbf' )

	(h, w) = gabors[0].shape

	x = packGaborImages(gabors)

	y = numpy.zeros((h, w))
	
	y[points[0][0]][points[0][1]] = 10.0
	y.resize(y.size, 1)
	y = numpy.hstack((y))

	print "Training SVM..."
		
	#Train the SVM
	svm.learn(x, y)

	svm.save_model('test_svm.xml')
		
	return svm


def predictFiducial():
		
	svm = mlpy.LibSvm.load_model('test_svm.xml')
	
	image = "/home/varun/Projects/FEAR/Dataset/cohn-kanade-images/S005/001/S005_001_00000001.png"
	landmarks = "/home/varun/Projects/FEAR/Dataset/Landmarks/S005/001/S005_001_00000001_landmarks.txt"
	
	points = utils.getPoints(landmarks)
	
	gabor = fear.getGaborImages(image)
	x = packGaborImages(gabor)
	
	y = svm.pred(x)

	img = cv2.imread(image)
	(h, w, c) = img.shape

	
	#utils.mark(image, points[0][0], points[0][1])
	print y[points[0][0]*h + points[0][1]]
	
	#for i in y:
	#	print i
			#utils.mark(image, i/490, i%640)
	print y

								
if __name__ == "__main__":
	#getGaborImages('../sample.jpg')
	#show_dataset()
	predictFiducial()
