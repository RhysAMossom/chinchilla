#! /usr/bin/env python
import sys
import optparse
import pygame

if __name__ == "__main__":
	parser = optparse.OptionParser()
	parser.add_option("-l", "--leds", dest = "leds", default=60, help="Number of LEDs")
	parser.add_option("-W", "--width", dest = "width", default=800, help="Windows width")
	parser.add_option("-H", "--height", dest = "height", default=480, help="Windows height")
	(options, args) = parser.parse_args()
	
	#create the screen
	pygame.init() 
	window = pygame.display.set_mode((options.width, options.height)) 
	
	pygame.draw.rect(window, (255, 255, 255), pygame.rect((0, 0), (30, 0), (0,30),(30,30)))
	
	padding = 1
	pixel_w = (options.width - 2*padding)/options.leds
	pixel_h = pixel_w
	
	for x in range(padding, options.width - pixel_w, pixel_w):
		pygame.draw.rect(window, (x % 255,(x-100) % 255,255), (x,100,pixel_w,pixel_h),0)
	
	#draw it to the screen
	pygame.display.flip() 

	#input handling (somewhat boilerplate code):
	while True:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				print event
				sys.exit(0) 
			else:
				print event 
