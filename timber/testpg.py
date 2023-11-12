import math
import pygame as pg
import sys

pg.init()
FPS = 60
clock = pg.time.Clock()
width, height = 800, 1000
radius = 10
offset = 0
x = radius
y0 = height - radius
y = height - radius
g = 9.81
Rm = 300 + radius
theta = 1.10714871779409
u = math.sqrt((g * Rm) / math.sin(2*theta))
tmax = Rm / (u  * math.cos(theta))
print(tmax)
t = 0
isJumping = False
window = pg.display.set_mode((width, height))
pg.display.set_caption("test projectile")

while True:
    clock.tick(FPS)
    dt = clock.get_time()
    for event in pg.event.get():
        if event.type == pg.QUIT:
            pg.quit()
    keys = pg.key.get_pressed()
    if keys[pg.K_SPACE]:
        if not isJumping:
            isJumping = True
            offset = x + radius
    if isJumping:
        x = u * math.cos(theta) * t + radius + offset
        y = y0 - (u*math.sin(theta) * t - 0.5*g*t**2)
        if x > width - radius or t>tmax:
            y = height -radius
            x = min(x, width -radius)
            isJumping = False
            t = 0

        t += 0.1
        
        
    window.fill((0, 0, 0))
    pg.draw.circle(window, (255, 255, 255), (x, y), radius)
    pg.display.update()
