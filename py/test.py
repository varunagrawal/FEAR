import gabor
import cv
import cv2
import numpy

def getGaborImages():

	x = cv2.imread('../sample.jpg')

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
			dst = cv.CreateMat(h, w, cv.CV_32FC1)

			cv.Filter2D(cv.fromarray(src), dst, kernel)

			gabors.append(numpy.asarray(dst))


	for i in gabors:
		cv2.imshow("Gabor Image", i)
		cv2.waitKey(0)
	
	return gabors



if __name__ == "__main__":
	getGaborImages()
