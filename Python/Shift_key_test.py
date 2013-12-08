import pygame as pg
run = True
pg.init()
while run:
        # Keyboard
        for event in pg.event.get():
            if event.type == pg.QUIT:   
                run = False
                 
            # User let up on a key (we do not care if he pressed it down)
            if event.type == pg.KEYUP:
                if event.key == pg.K_f:
                    if(pg.key.get_pressed()[pg.K_RSHIFT] or pg.key.get_pressed()[pg.K_LSHIFT]):
                        print "F"
                    else:
                        print "f"
                if event.key == pg.K_ESCAPE:
                    run = False
                    
pg.close()
