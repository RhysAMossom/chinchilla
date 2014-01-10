#! /usr/bin/env python
import sys
import optparse
import pygame

if __name__ == "__main__":
	parser = optparse.OptionParser()
	parser.add_option("-l", "--leds", dest = "leds", default=60, help="Number of LEDs")
	parser.add_option("-W", "--width", dest = "width", default=680, help="Windows width")
	parser.add_option("-H", "--height", dest = "height", default=480, help="Windows height")
	(options, args) = parser.parse_args()
	
	
	pygame.init() 
	
	#create the screen
	window = pygame.display.set_mode((options.width, options.height)) 

	#draw a line - see http://www.pygame.org/docs/ref/draw.html for more 
	pygame.draw.line(window, (255, 255, 255), (0, 0), (30, 50))
	pygame.draw.rect(window, (255, 255, 255), pygame.rect((0, 0), (30, 0), (0,30),(30,30)))
	
	pixel_w = options.width/options.leds
	pixel_h = pixel_w
	
	for x in range(0,options.width, options.width):
		pygame.draw.rect(window, (0,0,0), (0,0), (x,pixel_h))
	
	#draw it to the screen
	pygame.display.flip() 

	#input handling (somewhat boilerplate code):
	while True: 
	   for event in pygame.event.get(): 
		  if event.type == pygame.QUIT: 
			  sys.exit(0) 
		  else: 
			  print event 
