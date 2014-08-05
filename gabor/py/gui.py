#!/usr/bin/python

from Tkinter import *
import Image, ImageTk
import tkFileDialog



def loadfile():
	#statusbar.config(text = imgfile.show())

	global label, img, photo, imgfile
	del(label)
	del(img)
	del(photo)
	del(imgfile)

	imgfile = tkFileDialog.Open(root)
	loadimage(imgfile)

def loadimage(imgfile):
	global label, img, photo
	
	img = Image.open(imgfile.show())
	photo = ImageTk.PhotoImage(img)
	label = Label(root, image=photo)
	label.pack(side=TOP)

	return label

root = Tk()
root.title("FEAR")

imgfile = tkFileDialog.Open(root)
label = loadimage(imgfile)

Button(root, text="Select New Image", command=loadfile).pack()

statusbar = Label(root, text="", bd=1, relief=SUNKEN, anchor=W)
statusbar.pack(side=BOTTOM, fill=X)


root.mainloop()
