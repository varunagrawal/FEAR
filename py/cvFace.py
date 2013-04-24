from cv import *
from cv2 import *

face_cascade = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml"

def detect_face(image):
	#Load the classifiers
	haarFace = Load(face_cascade)

	#Run the classifiers
	storage = CreateMemStorage()
	
	detectedFace = HaarDetectObjects(image, haarFace, storage)
	print "Faces detected"
	
	if detectedFace:
		for face in detectedFace:
			Rectangle(image, (face[0][0], face[0][1]),
					  (face[0][0]+face[0][2], face[0][1]+face[0][3]), RGB(155, 255, 25), 2)

	NamedWindow('Face detection', CV_WINDOW_AUTOSIZE)
	ShowImage('Face detection', image)
	WaitKey(0)
	

def getImage():
	
	capture = CaptureFromCAM(0)
	while True:
		img = QueryFrame(capture)
		ShowImage("Webcam", img)
		k = WaitKey()
		if k == 27:
			break

	#del(camera)

	return img


def main():
	#image = getImage()
	detect_face(LoadImage('../sample.jpg'))
	

if __name__ == "__main__":
	main()

