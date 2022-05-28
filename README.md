# Brick Breaker
It's a simple graphical game. The objective of the game is to break the brick. I used `C++` as a programming
language and `GLUT` (OpenGL Utility Toolkit) to construct the structure of the game.

## Rules of the Game:
- If the player break the brick the game will goes on...
- Until all the brick breaks or player faild to break the brick the game is over.

# How the Game Works
Now, there will be a cube, a block at the bottom of the screen, and a total number of 45 bricks. The cube will go up and down, and try to hit one of the bricks, if it becomes successful in doing so the brick that was hit will be removed. The game will continue until the cube misses the block at the bottom after hitting a brick or after going downward, or it hits all of the bricks one by one.

## Instructions:
- To `move` the block use the `LEFT` key or `RIGHT` key of the keyboard.

## Demo GIF:
![img](https://github.com/SaruarChy/Brick-Breaker-OpenGL/blob/main/Brick%20Breaker.gif) 

# Functions
I have taken following functons in order to complete the project.
- void initialize();	//To set the initial co-ordinates of the objects on the screen
- bool check_collision(float, float, float, float, float, float, float, float); //Function for checking collision
- void draw();		//Render the objects on the screen using the latest updated co-ordinates
- void reshape();		//Modify the co-ordinates according to the key-presses and collisions etc...
- void specialUp(int,int, int); //Checks for Key Press
- void specialDown(int, int, int); //Checks for Key Release
- void revert();

## Procuders to `Run` this Game on your machine
In order to run this game, you need to follow these steps -
- Make sure your machine have `Code::Blocks IDE` and `GLUT` installed
- Then just press `Build` & `Run` to run this project.
- Enjoy the game.

> :memo: **Note:** This project code is written on Windows OS.
> ⬇️: **Download:** You can download the whole project folder (as zip) from [here] (https://github.com/SaruarChy/Brick-Breaker-OpenGL/archive/refs/heads/main.zip)
