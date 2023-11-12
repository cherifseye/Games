from typing import Any
import pygame
import sys
import os
import random

img_dir = os.path.join(os.path.dirname(__file__), "Icons")

def ressource_path(relative_path):
    base_path = getattr(sys, '_MEIPASS', os.path.dirname(os.path.abspath(__file__)))
    return os.path.join(base_path, relative_path)

imag_dir = ressource_path("assets")

# Initialize pygame
pygame.init()

# Set up constants
FPS = 60
SCREEN_WIDTH = 798
SCREEN_HEIGHT = 600

# Create the game window
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Car Racing Game")

# Load images
BG_IMAGE_PATH = ressource_path('assets/bg.png')
CAR_IMAGE_PATH = ressource_path('assets/car1.jpeg')
OBSTACLES_IMAGE_PATH = ressource_path('assets/car2.png')

bg = pygame.image.load(BG_IMAGE_PATH).convert_alpha()
car_image = pygame.image.load(CAR_IMAGE_PATH).convert_alpha()
obstacles = pygame.image.load(OBSTACLES_IMAGE_PATH).convert_alpha()

# Initial positions for the car and background
car_x = 180
car_y = SCREEN_HEIGHT - 95
other_x = random.randint(180, 490)
other_y = random.randint(0, SCREEN_HEIGHT - 95)
bg_y = 0

clock = pygame.time.Clock()

class Car:
    def __init__(self, x, y, image):
        self.x = x
        self.y = y
        self.image = image

    def draw(self, win):
        win.blit(self.image, (self.x, self.y))

def draw_background():
    screen.blit(bg, (0, bg_y))
    screen.blit(bg, (0, bg_y - SCREEN_HEIGHT))

def draw_game(car, obstacles_car):
    car.draw(screen)
    obstacles_car.draw(screen)

main_car = Car(car_x, car_y, car_image)
obstacles_list = []

# Create initial obstacles and add them to the list
num_obstacles = 3  # Adjust the number of obstacles as needed
min_obstacle_distance = 100  # Minimum distance between obstacles

for _ in range(num_obstacles):
    while True:
        obstacle_x = random.randint(180, 490)
        obstacle_y = random.randint(0, SCREEN_HEIGHT - 95)
        
        # Check for overlap with existing obstacles
        overlap = False
        for obstacle in obstacles_list:
            if (
                abs(obstacle_x - obstacle.x) < min_obstacle_distance
                and abs(obstacle_y - obstacle.y) < min_obstacle_distance
            ):
                overlap = True
                break
        
        if not overlap:
            obstacles_list.append(Car(obstacle_x, obstacle_y, obstacles))
            break



def check_collision(car1, car2):
    car1_rect = car1.image.get_rect()
    car1_rect.topleft = (car1.x, car1.y)
    
    car2_rect = car2.image.get_rect()
    car2_rect.topleft = (car2.x, car2.y)
    
    return car1_rect.colliderect(car2_rect)

game_over = False
score = 0

while True:
    clock.tick(FPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    keys = pygame.key.get_pressed()
    if not game_over:
        if keys[pygame.K_UP]:
            car_y -= 2
            if car_y == 5:
                car_y = SCREEN_HEIGHT - 95
        elif keys[pygame.K_DOWN] and car_y < SCREEN_HEIGHT - 95:
            car_y += 2
        elif keys[pygame.K_LEFT] and car_x > 180:
            car_x -= 1.5
        elif keys[pygame.K_RIGHT] and car_x < 540 - 50:
            car_x += 1.5
    bg_y = (bg_y + 1) % SCREEN_HEIGHT

    if not game_over:
        # Update obstacle cars' positions
        for obstacle in obstacles_list:
            obstacle.y = (obstacle.y + 1) % SCREEN_HEIGHT

        screen.fill((0, 0, 0))
        draw_background()

        # Update main_car position and draw
        main_car.x = car_x
        main_car.y = car_y

        # Draw the main car
        main_car.draw(screen)

        # Check for collisions with obstacle cars
        collision = any(check_collision(main_car, obstacle) for obstacle in obstacles_list)

        # Draw and update each obstacle car
        for obstacle in obstacles_list:
            draw_game(main_car, obstacle)

        pygame.display.update()

        if collision:
            game_over = True
            print("Collision detected! Game over.")  
    else:
        # Handle game over state here
        screen.fill((0, 0, 0))
        game_over_font = pygame.font.Font(None, 64)
        game_over_text = game_over_font.render("Game Over", True, (255, 0, 0))
        game_over_rect = game_over_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2))
        screen.blit(game_over_text, game_over_rect)

        restart_font = pygame.font.Font(None, 32)
        restart_text = restart_font.render("Press R to Restart", True, (255, 255, 255))
        restart_rect = restart_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 50))
        screen.blit(restart_text, restart_rect)

        pygame.display.update()

        if keys[pygame.K_r]:
            # Reset the game state
            game_over = False
            car_x = 180
            car_y = SCREEN_HEIGHT - 95
            obstacles_list = []
            score = 0
            for _ in range(num_obstacles):
                while True:
                    obstacle_x = random.randint(180, 490)
                    obstacle_y = random.randint(0, SCREEN_HEIGHT - 95)
                    
                    # Check for overlap with existing obstacles
                    overlap = False
                    for obstacle in obstacles_list:
                        if (
                            abs(obstacle_x - obstacle.x) < min_obstacle_distance
                            and abs(obstacle_y - obstacle.y) < min_obstacle_distance
                        ):
                            overlap = True
                            break
                    
                    if not overlap:
                        obstacles_list.append(Car(obstacle_x, obstacle_y, obstacles))
                        break

    pygame.display.update()