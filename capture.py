import cv2

def getImage(camera):
    retval, im = camera.read()
    return im

def capture():
    camera_port = 0
    ramp_frames = 20
    camera = cv2.VideoCapture(camera_port)
    for i in xrange(ramp_frames):
        temp = getImage(camera)
    camera_capture = getImage(camera)
    cv2.imwrite("capture.png", camera_capture)
    del(camera)


