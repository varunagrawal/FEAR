from cv import *
from cv2 import *
import os

def mark(f, x, y):

	img = imread(f)
	circle(img, (x, y), 3, Scalar(0, 0, 255), -1, 7)

	imshow("Landmark", img)
	WaitKey(0)

def getPoints(landmark_file):
	p = open(landmark_file)
	imp = [17, 19, 21, 22, 24, 26, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 51, 54, 57, 60, 62, 64, 66]
	points = []
	s = t = []
	
	for line in p:
		s.append(line.split('   '))

	t = [s[i] for i in range(len(s)) if i in imp]
		
	#print t
	points = [[ int(float(x)), int(float(y)) ] for w, x, y in t]
	
	return points
	
	
def main():
	image_file = '../Dataset/cohn-kanade-images/S010/001/S010_001_00000014.png'
	landmark_file = '../Dataset/Landmarks/S010/001/S010_001_00000014_landmarks.txt'
	points =  getPoints(landmark_file)

	for point in points:
		mark(image_file, point[0], point[1])

if __name__ == "__main__":
	main()
