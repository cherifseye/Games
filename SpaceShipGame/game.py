import pygame as pg
import sys
import random


fps = 60

window_width= 800
window_height = 500
initial_meteor_pos = 10
meteor_Spped_max = 5
spaceShip_speed = 4

class Game:

    def __init__(self):
        self.i = 1
        pg.init()
        self.screen = pg.display.set_mode((window_width, window_height))
        pg.display.set_caption("Spaceship meteors")
        self.clock = pg.time.Clock()
        self.spaceShip = SpaceShip(self)
        self.meteors = [Metors(self) for _ in range(25)]
        self.font = pg.font.Font(None, 50)
        self.gameOver = False
 
    
    def draw_meteors(self):
        for meteor in self.meteors:
            meteor.move_Down()
            meteor.draw()


    def checkCollision(self):
        for meteor in self.meteors:
            if self.spaceShip.rect().colliderect(meteor.rect()):
                return True
        return False

    def drawGameOver(self):
        self.screen.fill((255, 255, 255))
        game_over_label = self.font.render(f"Game Over!!!", True, (255, 0, 0))
        options_label   = self.font.render(f"Press R to play gain or Q to quit", True, (255, 0, 0))
        self.screen.blit(game_over_label, (window_width / 3, window_height //3))
        self.screen.blit(options_label, (window_width/3 - 150, window_height // 3 + 100))

    def play(self):
        is_running = True
        while is_running:
            self.clock.tick(fps)
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    pg.quit()
                    sys.exit()
                    
            if not self.gameOver:
                keys = pg.key.get_pressed()
    
                if keys[pg.K_LEFT]:
                    self.spaceShip.move_Left()
    
                elif keys[pg.K_RIGHT]:
                    self.spaceShip.move_Right()
    
                elif keys[pg.K_UP]:
                    self.spaceShip.move_UP()
    
                elif keys[pg.K_DOWN]:
                    self.spaceShip.move_Down()
    
                if keys[pg.K_s]:
                    self.spaceShip.shoot()
    
                self.screen.fill((0, 0, 0))
                self.spaceShip.draw()
                self.draw_meteors()
                if self.checkCollision():
                    self.gameOver = True
            else:
                self.drawGameOver()
                keys = pg.key.get_pressed()
                if keys[pg.K_r]:
                    self.spaceShip.x = window_width / 2
                    self.spaceShip.y = window_height - 40
                    self.meteors = [Metors(self) for _ in range(25)]
                    self.gameOver = False
              
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