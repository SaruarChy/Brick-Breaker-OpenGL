/*+-----------------------------------------------+
  |                                               |
  |          Saruar Rahman Chowdhury              |
  |            Brick Breaker OpenGL               |
  |                                               |
  +-----------------------------------------------+*/
#include<GL/glut.h>
#include<stdlib.h>

// Bricks
struct bricks{
    float x, y, w, h; // coordinates
    bool alive; // checks hit or not
} b[45]; //a total of 45 bricks

float red1,red2,green1,green2,blue1,blue2; // alternate RGB sequence for odd and even brick

// cube
struct cube{
    float cubex, cubey, cubesz, velx, vely; // coordinates
    float red, green, blue; // colors
    bool left,right,up,down; // directions
} cube;

// Block at the bottom to catch the cube
struct block{
    float myx, myy; // coordinates
    float width, height; // dimensions
    bool lft, rgt; // direction of movement
    float red, green, blue; // colors
} block;

float red = 0, green = 0, blue = 0;

//To set the initial co-ordinates of the objects on the screen
void initialize(){
    for(int n=0,x=4,y=375; n<45; n++,x+=66){
        if(x > 560){
            x = 4;
            y -= 25;
        }
        b[n].x = x;
        b[n].y = y;
        b[n].w = 60;
        b[n].h = 20;
        b[n].alive = true;
    }

    block.myx = 300;
    block.myy = 0;
    block.width = 80;
    block.height = 20;
    block.lft = false;
    block.rgt = false;

    cube.cubex = 300;
    cube.cubey = 150;
    cube.cubesz = 20;
    cube.velx = 2.00;
    cube.vely = 2.00;

    red1 = 0.878;
    green1 = 1;
    blue1 = 1;
    red2 = 0.6;
    green2 = 0.8;
    blue2 = 0.196078;

    cube.red = 0.65;
    cube.green = 0.49;
    cube.blue = 0.24;

    block.red = 1;
    block.green = 0;
    block.blue = 0;

}

//Function for checking collision
bool check_collision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh){
    if( Ay+Ah < By )
        return false; //if A is more to the lft than B
    else if( Ay > By+Bh )
        return false; //if A is more to rgt than B
    else if( Ax+Aw < Bx )
        return false; //if A is higher than B
    else if( Ax > Bx+Bw )
        return false; //if A is lower than B

    return true; //There is a collision because none of above returned false
}

//Render the objects on the screen using the latest updated co-ordinates
void draw(){
    for(int i=0; i<45; i++){
        if(b[i].alive == true){
            if(i%2 == 0)
                glColor3f(red1,green1,blue1);
            else
                glColor3f(red2,green2,blue2);
                glBegin(GL_POLYGON);
                glVertex2f(b[i].x,b[i].y);
                glVertex2f(b[i].x+b[i].w,b[i].y);
                glVertex2f(b[i].x+b[i].w,b[i].y+b[i].h);
                glVertex2f(b[i].x,b[i].y+b[i].h);
                glEnd();
        }
    }

    glColor3f(block.red,block.green,block.blue);
    glBegin(GL_POLYGON);
    glVertex2f(block.myx,block.myy);
    glVertex2f(block.myx+block.width,block.myy);
    glVertex2f(block.myx+block.width,block.myy+block.height);
    glVertex2f(block.myx,block.myy+block.height);
    glEnd();

    glColor3f(cube.red,cube.green,cube.blue);
    glBegin(GL_POLYGON);
    glVertex2f(cube.cubex,cube.cubey);
    glVertex2f(cube.cubex+cube.cubesz,cube.cubey);
    glVertex2f(cube.cubex+cube.cubesz,cube.cubey+cube.cubesz);
    glVertex2f(cube.cubex,cube.cubey+cube.cubesz);
    glEnd();
    glutPostRedisplay();
    glutSwapBuffers();

}
//Modify the co-ordinates according to the key-presses and collisions etc...
void reshape(){
    if(block.myx < 0)
        block.myx = 0;
    if(block.myx+block.width > 600)
        block.myx = 520;
    if(block.lft == true)
        block.myx = block.myx-0.175;
    if(block.rgt == true)
        block.myx = block.myx+0.175;



    cube.cubex += 0.075*cube.velx;
    cube.cubey += 0.075*cube.vely;

    for(int n=0; n<45; n++){
        if(b[n].alive == true){
            if(check_collision(cube.cubex,cube.cubey,cube.cubesz,cube.cubesz,b[n].x,b[n].y,b[n].w,b[n].h)==true){
                cube.vely =- cube.vely;
                b[n].alive = false;
                cube.down = true;
                cube.up = false;
                break;
            }
        }
    }
    if(cube.cubex < 0){
        cube.velx =- cube.velx;
        cube.right = true;
        cube.left = false;
    }
    if(cube.cubex + cube.cubesz > 600){
        cube.right = false;
        cube.left = true;
        cube.velx =- cube.velx;
    }
    if(cube.cubey + cube.cubesz > 400)
        cube.vely =- cube.vely;
    else if(cube.cubey<0)
        exit(0);

    if(check_collision(cube.cubex,cube.cubey,cube.cubesz,cube.cubesz,block.myx,block.myy,block.width,block.height)==true){
        cube.vely =- cube.vely;
        cube.up = true;
        cube.down = false;
    }
    draw();
}
void specialUp(int key,int x,int y) //Checks for Key Press
{
    switch(key){
        case (GLUT_KEY_LEFT):
            block.lft = false;
            break;
        case (GLUT_KEY_RIGHT):
            block.rgt = false;
            break;
    }
}
//Checks for Key Release
void specialDown(int key,int x,int y){
    switch(key){
        case (GLUT_KEY_LEFT):
            block.lft = true;
            break;
        case (GLUT_KEY_RIGHT):
            block.rgt = true;
            break;
    }
}

void myinit(){
    glViewport(0,0,600,400);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,600,0,400);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(red,green,blue,1);
    glDisable(GL_DEPTH_TEST);
    draw();
    glFlush();
    reshape();
}

void revert(){
    cube.velx = 2.00;
    cube.vely = 2.00;
    if(cube.up == true){
        if(cube.right == true){
            cube.velx = cube.velx;
            cube.vely = cube.vely;
        }
        else if(cube.left == true){
            cube.velx =- cube.velx;
            cube.vely = cube.vely;
        }
    }
    else if(cube.down = true){
        if(cube.right = true){
            cube.velx = cube.velx;
            cube.vely =- cube.vely;
        }
        else if(cube.left == true){
            cube.velx =- cube.velx;
            cube.vely =- cube.vely;
        }
    }
}
int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitWindowSize(600,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Brick Breaker");
    initialize();
    myinit();
    draw();
    glutDisplayFunc(display);
    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);
    glutIdleFunc(reshape);
    glutMainLoop();
    return 0;
}
