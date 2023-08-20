import pygame as pg
import sys
import random


fps = 60

window_width= 800
window_height = 500
initial_meteor_pos = 10
meteor_Spped_max = 5
spaceShip_speed = 2

class Game:

    def __init__(self):
        
        pg.init()
        self.screen = pg.display.set_mode((window_width, window_height))
        pg.display.set_caption("Spaceship meteors")
        self.clock = pg.time.Clock()
        self.spaceShip = SpaceShip(self)
        self.meteor_test = [Metors(self) for _ in range(10)]
    
    def draw_meteors(self):
        for meteor in self.meteor_test:
            meteor.move_Down()
            meteor.draw()
            

    def play(self):
        is_running = True
        while is_running:
            self.clock.tick(fps)
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    pg.quit()
                    sys.exit()
            
            keys = pg.key.get_pressed()

            if keys[pg.K_LEFT]:
                self.spaceShip.move_Left()

            elif keys[pg.K_RIGHT]:
                self.spaceShip.move_Right()

            elif keys[pg.K_UP]:
                self.spaceShip.move_UP()

            elif keys[pg.K_DOWN]:
                self.spaceShip.move_Down()

            self.screen.fill((0, 0, 0))
            self.spaceShip.draw()
            self.draw_meteors()
            pg.display.update()


class GameObject:

    def load_image(self, filename):
        self.image  = pg.image.load(filename).convert()
        self.width  = self.image.get_width()
        self.height = self.image.get_height()
    
    def rect(self):
        return pg.Rect(self.x, self.y, self.width, self.height)
    
    def draw(self):
        self.game.screen.blit(self.image, (self.x, self.y))


class SpaceShip(GameObject):
    def __init__(self, game):
        self.game = game
        self.x = window_width / 2
        self.y = window_height - 40
        self.load_image('assets/starship.png')

    def move_Left(self):
        if self.x > 0:
            self.x -= spaceShip_speed

    def move_Right(self):
        if self.x < window_width - 40:
            self.x += spaceShip_speed

    def move_UP(self):
        if self.y >= 0:
            self.y -= spaceShip_speed

    def move_Down(self):
        if self.y < window_height - 40:
            self.y += spaceShip_speed

class Metors(GameObject):
    def __init__(self, game):
        self.game = game
        self.x = random.randint(0, window_width - 40)
        self.y = initial_meteor_pos
        self.speed = random.randint(1, meteor_Spped_max)
        self.load_image('assets/meteor.png')

    def move_Down(self):
        self.y += self.speed
        if self.y > window_height:
            self.y = -self.height
            self.x = random.randint(0, window_width -40)
