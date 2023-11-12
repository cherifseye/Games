#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>

using namespace sf;
const int width  = 1920; 
const int height = 1080;
bool paused      = true;

const int treeWidth  = 300;
const int treeHeight = 900;
float treeXpos       = 810;
const int ground     = treeHeight;

const int playerWidth  = 150;
const int playerheight = 192;
const float thetajump  = 1.10714871779409f;
float playerGround     = ground - playerheight;
float playerYpos       = ground - playerheight;
float Rm               = 400;
float g                = 9.81;
float theta            = 1.10714871779409;
float u                = sqrt((g*Rm) / sin(2*theta));
float tmax             = Rm / (u * cos(theta));
float offset           = 0;
float t                = 0;
const float wallplayer = width - playerheight; 
float playerheightMax  = playerGround - 2*playerheight;
float playerXpos       = treeXpos - playerWidth;
bool playerIsJumping   = false;
bool playerIsMovingUp  = false;
bool isJumpingLeft     = false;
bool isJumpingRight    = false;
float playerSpeed      = 0.5f;


const int numClouds   = 3;
const int cloudWidth  = 300;
const float wallCloud = width - cloudWidth;
bool  isCloudActive   = false;
std::vector<float> cloudposX(3, 0.0f);
std::vector<float> cloudPosY   = {50.0f, 250.0f, 450.0f};
std::vector<float> cloudSpeeds = {0.350f, 0.125f, 0.25f}; 


float beePositionX     =  0.0f;
float beePositionY     = 650.0f;
float beeSpeed         = 0.80f;
float beeSpeedModifier = 1.0f;
bool isBeeActive       = false;
bool BeeMoveRight      = true;
int beeDimX            = 60;
int beeDimY            = 40;
float wallBee          = width - beeDimX;
float beeWaveAmplitude = 300.0f;
float beeWaveFrequency = 5.0f;

int numBranch          = 6;

std::string messageStr     = "Press Space to play the game";
std::string gameOverStr    = "Game Over, Press Space to play again";
std::string PausedStr      = "Press Space to Keep Playing";
const float textFontsize   =   48;
std::string scoreText;
int score                  = 0;

float barTimerWidth  = width /2;
const float bartimerHeight = 80;

bool gameOver = false;

void messageOrigin(Text text){
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin((textRect.width/2), (textRect.height /2));
}

int main(){

    Clock clock;
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber", Style::Default);

    Texture backgroundTexture, treeTexture, beeTexture, cloudTexture, playerTexture, branchTexture;
    backgroundTexture.loadFromFile("graphics/background.png");
    treeTexture.loadFromFile("graphics/tree.png");
    beeTexture.loadFromFile("graphics/bee.png");
    cloudTexture.loadFromFile("graphics/cloud.png");
    playerTexture.loadFromFile("graphics/player.png");
    branchTexture.loadFromFile("graphics/branch.png");
    Sprite bcgSprite, treeSprite, beeSprite, playerSprite;
    std::vector<Sprite> cloudSprites(numClouds);
    std::vector<Sprite> branchSprite(numBranch);
    for (int cloud=0; cloud<numClouds; cloud++){
        cloudSprites[cloud].setTexture(cloudTexture);
        cloudSprites[cloud].setPosition(cloudposX[cloud], cloudPosY[cloud]);
    }

    for (int branch=0; branch<numBranch; branch++){
        branchSprite[branch].setTexture(branchTexture);
        float height = branch*100.0f;
        if (branch % 2 == 0){
            branchSprite[branch].setPosition(1110, height);
        }else{
            branchSprite[branch].setRotation(180);
            branchSprite[branch].setPosition(810, height);
        }

    }
    //branchSprite[0].setPosition(1110, 150);

    bcgSprite.setTexture(backgroundTexture);
    bcgSprite.setPosition(0, 0);

    treeSprite.setTexture(treeTexture);
    treeSprite.setPosition(treeXpos, 0);

    beeSprite.setTexture(beeTexture);
    beeSprite.setPosition(beePositionX, beePositionY);

    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(playerXpos, playerYpos);
    
    Font font;
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf")){
        return 1; 
    }
    Text messagetext;
    Text scoreText;

    messagetext.setString(messageStr);
    messagetext.setFont(font);
    messagetext.setCharacterSize(static_cast<u_int> (textFontsize));
    messagetext.setFillColor(Color::Red);
    messageOrigin(messagetext);

    scoreText.setString("Score = " + std::to_string(score));
    scoreText.setFont(font);
    scoreText.setCharacterSize(textFontsize);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(0, 0);

    RectangleShape timerBar;
    timerBar.setSize(Vector2f(barTimerWidth, bartimerHeight));
    timerBar.setPosition(10, height-85);
    timerBar.setFillColor(Color::Red);

    SoundBuffer chopBuffer, gameOverBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    gameOverBuffer.loadFromFile("sound/out_of_time.wav");
    Sound chop, gameOverSound;
    chop.setBuffer(chopBuffer);
    gameOverSound.setBuffer(gameOverBuffer);

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asMilliseconds();
        Event event;
        if (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Space)){
            if (paused){
                chop.play();
                if (gameOver){
                    messagetext.setString(messageStr);
                    messageOrigin(messagetext);
                    gameOver = false;
                };
                if (!isBeeActive && !isCloudActive){
                paused = false;
                isBeeActive   = true;
                isCloudActive = true;
                }
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape)){
            if (!paused){
                messagetext.setString(PausedStr);
                paused = true;
                isBeeActive = false;
                isCloudActive = false;
            }
        }
        
        if (!paused){
        if (isBeeActive){
            beePositionX = beePositionX + beeSpeed*beeSpeedModifier*deltaTime;

            if (beePositionX > wallBee || beePositionX < 0){
                beePositionX = std::max(0.0f, std::min(beePositionX, wallBee));
                beeSpeed = -beeSpeed;
            }
            srand(time(NULL));
            beeSpeedModifier = static_cast<float>(rand() % 20 + 2.5) / 10.0f;
            beePositionY = 650.0f + beeWaveAmplitude * sin(beeWaveFrequency * beePositionX /width); 
            beeSprite.setPosition(beePositionX, beePositionY);
        }

        if (isCloudActive){
            for (int i=0; i<numClouds; i++){
                cloudposX[i] = cloudposX[i] + cloudSpeeds[i] * deltaTime;
            }
            for (int i=0; i<numClouds; i++){
                if(cloudposX[i] > wallCloud || cloudposX[i] < 0){
                    cloudposX[i] = std::max(0.0f, std::min(cloudposX[i], wallCloud));
                    cloudSpeeds[i] = -cloudSpeeds[i];
                }
            }            

            for (int cloud=0; cloud<numClouds; cloud++){
                cloudSprites[cloud].setPosition(cloudposX[cloud], cloudPosY[cloud]);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::R) || Keyboard::isKeyPressed(Keyboard::L)){
            if (!playerIsJumping && !playerIsMovingUp){
                playerIsJumping = true;
                offset = playerSprite.getPosition().x; 
            }
            if (Keyboard::isKeyPressed(Keyboard::R)){
                isJumpingRight = true;
                isJumpingLeft  = false;
            }else{
                isJumpingLeft  = true;
                isJumpingRight = false;
            }
        }
        
        if (!playerIsJumping){
            if (Keyboard::isKeyPressed(Keyboard::Up)){
                if (!playerIsMovingUp){
                    playerIsMovingUp = true;
                    playerheightMax  = ground - 2*playerheight;
                }
            }
            
            if(Keyboard::isKeyPressed(Keyboard::Left) && playerXpos > 0){
                if (!playerIsMovingUp)
                {
                    playerXpos = playerSprite.getPosition().x - playerSpeed * deltaTime;
                    playerSprite.setPosition(playerXpos, playerYpos);
                }else{
                    playerXpos = playerSprite.getPosition().x + playerSpeed * deltaTime;
                    playerheightMax = playerSprite.getPosition().y;
                    playerYpos = playerSprite.getPosition().y;
                    playerSprite.setPosition(playerXpos, playerYpos);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) && playerXpos < wallplayer){
                
                if (!playerIsMovingUp){
                    playerXpos = playerSprite.getPosition().x + playerSpeed * deltaTime;
                    playerSprite.setPosition(playerXpos, playerYpos);
                }else{
                    playerXpos = playerSprite.getPosition().x - playerSpeed * deltaTime;
                    playerheightMax = playerSprite.getPosition().y;
                    playerYpos = playerSprite.getPosition().y;
                    playerSprite.setPosition(playerXpos, playerYpos);
                }
            }
    
            if (playerIsMovingUp){
                playerYpos -= playerSpeed * deltaTime;
                if (playerYpos < playerheightMax){
                    playerYpos = playerheightMax;
                    playerSpeed = -playerSpeed;
                }
                if (playerYpos > playerGround){
                    playerYpos = playerGround;
                    playerIsMovingUp = false;
                    playerSpeed = -playerSpeed;
                }
                playerXpos = playerSprite.getPosition().x;
                playerSprite.setPosition(playerXpos, playerYpos);
            }
        }else{
            if (isJumpingRight){
                playerXpos = u *cos(theta) * t + offset;
            }else{
                playerXpos = -u*cos(theta) * t + offset;
            }
            playerYpos = playerGround - (u*sin(theta) * t - 0.5*g*pow(t, 2));

            if (playerXpos > wallplayer || t > tmax || playerXpos < 0){
                playerYpos = playerGround;
                playerXpos = std::max(0.0f, std::min(wallplayer, playerXpos));

                playerIsJumping = false;
                isJumpingRight  = false;
                isJumpingLeft   = false;
                t = 0;
            }
            playerSprite.setPosition(playerXpos, playerYpos);
            t += 10 * (deltaTime / 1000); // 10x acceleration for the purpose of the game

        }
        barTimerWidth -= 4*(deltaTime / barTimerWidth);
        timerBar.setSize(Vector2f(barTimerWidth, bartimerHeight));
        }

        if (barTimerWidth <=0){
            gameOver = true;
            isBeeActive   = false;
            isCloudActive = false;
        }

        if (gameOver){
            paused = true;
            barTimerWidth = width / 2;
            messagetext.setString(gameOverStr);
            messageOrigin(messagetext);
        }
        messagetext.setPosition(width/2.0f - messagetext.getLocalBounds().width /2.0f, height/2.0f);
        window.clear();
        window.draw(bcgSprite);
        window.draw(treeSprite);
        for (int i=0; i<numBranch; i++){
            window.draw(branchSprite[i]);
        }
        for (int cloud=0; cloud<numClouds; cloud++){
            window.draw(cloudSprites[cloud]);
        }
        window.draw(playerSprite);
        window.draw(beeSprite);
        window.draw(scoreText);
        if (paused || gameOver){
            if (gameOver){
                gameOverSound.play();
            }
            window.draw(messagetext);}
        window.draw(timerBar);
        window.display();   
       
    }
    
}