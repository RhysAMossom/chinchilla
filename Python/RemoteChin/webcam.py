# import the relevant libraries
import time
import pygame
import pygame.camera
from pygame.locals import *

# initialise the display window
w = 640
h = 480
screen = pygame.display.set_mode([w,h])
pygame.init()
pygame.camera.init()
# set up a camera object
for i in range(5):
    try:
        cam_address = "/dev/video"+str(i)
        cam = pygame.camera.Camera(cam_address,(w,h))
        # start the camera
        cam.start()
    except SystemError:
        pass
    else:
        break

if i > 5:
    print "No Camera Found"
    pygame.quit()
    exit()
else:
    print "Connected to camera at", cam_address

count = 0
while count <3:
    try:
        # sleep between every frame
        time.sleep( 0.05 )
        # fetch the camera image
        image = cam.get_image()
        # blank out the screen
        screen.fill([0,0,0])
        # copy the camera image to the screen
        screen.blit( image, ( 0, 0 ) )
        # update the screen to show the latest screen image
        pygame.display.update()
        pygame.image.save(image,"/home/carlitos/img"+str(count)+".jpg")
        count += 1
    except SystemError:
        break

pygame.quit()
