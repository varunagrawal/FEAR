# Utility functions for FEAR

import cv2
import numpy
import mlpy
import os


# Marks the landmark specified on the image
def mark(f, x, y):

	img = cv2.imread(f)
	cv2.circle(img, (x, y), 3, (0, 0, 255), -1, 7)

	cv2.imshow("Landmark", img)
	cv2.waitKey(0)

	return img


# Read landmarks file and get the important landmarks
def getPoints(landmark_file):

	p = open(landmark_file)

	imp_landmarks = [17, 19, 21, 22, 24, 26, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 51, 54, 57, 60, 62, 64, 66]

	points = []
	s = t = []
	
	for line in p:
		s.append(line.split('   '))

	t = [s[i] for i in range(len(s)) if i in imp_landmarks]
		
	#print t
	points = [[ int(float(x)), int(float(y)) ] for w, x, y in t]
	
	return points
