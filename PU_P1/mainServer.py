# MIT License
# 
# Copyright (c) 2022 Sukarna Jana
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

from random import random
from socket import timeout
from warnings import catch_warnings
import serial
import time
import cv2
import random
import time


# [MAIN]
# if mode is 1 it means it will take data from goggles 
# Part and control the Car
# if mode is 0 it means it will use OpenCV for detecting 
# and control the Car
Mode = 1
# Haarcascade file for detecting FACE
FaceHaarcascade = "/home/sukarna/Documents/PU_P1/haarcascade_frontalface_alt2.xml"
# Haarcascade file for detecting EYE
EyeHaarcascade = "/home/sukarna/Documents/PU_P1/haarcascade_eye.xml"
# [BOARD]
# Config the arduino board
Port = "/dev/ttyUSB0"
BoardRate = 9600
moved = 0
mode = 0

try:
    board  = serial.Serial(
        port=Port, 
        baudrate=BoardRate, 
        #parity=serial.PARITY_NONE,
        #stopbits=serial.STOPBITS_ONE,
        #bytesize=serial.EIGHTBITS,
        timeout=1 )
    board.flushInput()
    print("Connected to arduino")
except:
    print("Fail to connect to arduino")

def sendData(data):
    time.sleep(0.1)
    try:
        print(data)
        if(data==1):
            #garbageValue = random.randint(12,99)
            #board.write(b'1')
            board.write(b'RRRR')
        elif(data==11):
            #board.write(b'11')
            board.write(b'S')
        else:
            #board.write(b'10')
            board.write(b'E')
            
    except:
        print("Fail to send")
    #board.close()

# Load the cascade
face_cascade = cv2.CascadeClassifier(FaceHaarcascade)
eye_cascade = cv2.CascadeClassifier(EyeHaarcascade)
# To capture video from webcam. 
cam = cv2.VideoCapture(0)
while True:
    # Read the frame
    _, img = cam.read()
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect the faces
    faces = face_cascade.detectMultiScale(gray,1.1, 5)
    # Draw the rectangle around each face
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # Detect the faces
        eyes = eye_cascade.detectMultiScale(gray,1.2, 6)
        # Draw the rectangle around each face
        for (x, y, w, h) in eyes:
            cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 255), 2)
        # Display
        sendData(1)
        mode = 1
    # Display
    cv2.imshow('Show Output - by Sukarna Jana', img)
    # Stop if escape key is pressed

    if(mode==0):
        moved+=1

    if(moved>40):
        sendData(11)
        moved = 0

    k = cv2.waitKey(30) & 0xff
    if k==27:
        break
    mode = 0
# Release the VideoCapture object
cam.release()
