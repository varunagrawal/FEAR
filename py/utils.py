# Utility functions for FEAR

import cv2
import numpy
import mlpy
import os

landmarks_dict = { "l_o_eyebrow" : 0, "l_m_eyebrow" : 1, "l_i_eyebrow" : 2, "r_i_eyebrow" : 3, "r_m_eyebrow" : 4, "r_o_eyebrow" : 5, "l_o_eye" : 6, "l_um_eye" : 7, "l_i_eye" : 8, "l_lm_eye" : 9, "r_i_eye" : 10, "r_um_eye" : 11, "r_o_eye" : 12, "r_lm_eye" : 13, "l_o_lip" : 14, "up_o_lip" : 15, "r_o_lip" : 16, "low_o_eye" : 17, "r_i_lip" : 18, "up_i_lip" : 19, "l_i_lip" : 20, "low_i_lip" : 21 }


# Marks the landmark specified on the image
def mark(f, x, y):

	img = cv2.imread(f)
	cv2.circle(img, (x, y), 3, (0, 0, 255), -1, 7)

	cv2.imshow("Landmark", img)
	cv2.waitKey(0)

	return img


# Read landmarks file and get the important landmarks
def get_points(landmark_file):

	p = open(landmark_file)

	imp_landmarks = [17, 19, 21, 22, 24, 26, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 51, 54, 57, 60, 62, 64, 66]

	points = []
	s = t = []
	
	for line in p:
		s.append(line.split('   '))

	t = [s[i] for i in range(len(s)) if i in imp_landmarks]
		
	#print t
	points = [[ int(float(x)), int(float(y)) ] for w, x, y in t]

	points[7][0] = (points[7][0] + points[8][0]) / 2
	points[7][1] = (points[7][1] + points[8][1]) / 2
	
	points[10][0] = (points[10][0] + points[11][0]) / 2
	points[10][1] = (points[10][1] + points[11][1]) / 2
	
	points[13][0] = (points[13][0] + points[14][0]) / 2
	points[13][1] = (points[13][1] + points[14][1]) / 2

	points[16][0] = (points[16][0] + points[17][0]) / 2
	points[16][1] = (points[16][1] + points[17][1]) / 2
	
	del(points[8])
	del(points[10])
	del(points[12])
	del(points[14])
	
	return points



# Pack the images as list of image vectors
def pack_gabor_images(gabors):

	for g in gabors:
		g.resize(g.size, 1)

	x = gabors[0]
		
	for i in range(1, len(gabors)):
		x = numpy.hstack((x, gabors[i]))

	return x
