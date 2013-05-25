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
		image1 = os.path.join(image_root, f1)
		landmark1 = os.path.join(landmarks_root, f1)

		image2_list = os.listdir(image1)
		image2_list.sort()

		landmark2_list = os.listdir(landmark1)
		landmark2_list.sort()
		
		for f2 in image2_list:
				image2 = os.path.join(image1, f2)
				landmark2 = os.path.join(landmark1, f2)

				images = os.listdir(image2)
				images.sort()
				
				landmarks = os.listdir(landmark2)
				landmarks.sort()


				for i in range(len(images)):
						image_file = os.path.join(image2, images[i])
						landmark_file = os.path.join(landmark2, landmarks[i])

						print "File: %s" % image_file
			
						points = utils.get_points(landmark_file)
						
						gabors = fear.get_gabor_images(image_file)
						train_SVMs(gabors, points)

						#for x, y in points:
						#		utils.mark(image_file, x, y)



	
						
# Train SVMs to detect feature points. Input: List of Gabor images and array of feature point locations
def train_SVMs(gabors, points):
		
	svm = mlpy.LibSvm( svm_type='c_svc', kernel_type='rbf' )

	(h, w) = gabors[0].shape

	x = pack_gabor_images(gabors)

	y = numpy.zeros((h, w))
	
	y[points[0][0]][points[0][1]] = 10.0
	y.resize(y.size, 1)
	y = numpy.hstack((y))

	print "Training SVM..."
		
	#Train the SVM
	svm.learn(x, y)

	svm.save_model('svm.model')
		
	return svm


def predict_fiducial():
		
	svm = mlpy.LibSvm.load_model('svm.model')
	
	image = "/home/varun/Projects/FEAR/Dataset/cohn-kanade-images/S005/001/S005_001_00000001.png"
	landmarks = "/home/varun/Projects/FEAR/Dataset/Landmarks/S005/001/S005_001_00000001_landmarks.txt"
	
	points = utils.get_points(landmarks)
	
	gabor = fear.get_gabor_images(image)
	x = pack_gabor_images(gabor)
	
	y = svm.pred(x)

	img = cv2.imread(image)
	(h, w, c) = img.shape
	
	#utils.mark(image, points[0][0], points[0][1])
	print y[points[0][0]*h + points[0][1]]
	
	#for i in range(len(x)):
	for i in y:
		#y = svm.pred(numpy.array(x[i]))
		if i > 0.0:
			print i

			#utils.mark(image, i/490, i%640)
	print y


def test():
	image = "/home/varun/Projects/FEAR/Dataset/cohn-kanade-images/S010/001/S010_001_00000001.png"
	landmarks = "/home/varun/Projects/FEAR/Dataset/Landmarks/S010/001/S010_001_00000001_landmarks.txt"

	"""
	img = cv2.imread(image)
	points = utils.get_points(landmarks)
	for i in points:
		utils.mark(image, i[0], i[1])
	"""
	img = cv2.imread(image)
	fear.detect_mouth(img)

if __name__ == "__main__":
	#img = cv2.imread('../sample.jpg')
	#cv2.imshow("Original Image", img)
	#cv2.waitKey(0)

	#gabors = fear.getGaborImages('../sample.jpg')

	"""for g in gabors:	
		cv2.imshow("Gabor Image", g)
		cv2.waitKey(0)
		"""

	#show_dataset()
	#predict_fiducial()

	test()
