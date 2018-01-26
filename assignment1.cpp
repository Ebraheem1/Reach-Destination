//  Includes

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include <math.h>
#include <stdio.h>
//---------------------------
//  Methods Signatures
void Display();
void drawStickMan();
void spe(int k, int x, int y);
void drawPowerUp();
void drawObstacleA();
void Anim();
void bringEveryThingBack();

//-----------------
//  Global Variables
bool power = false;
Mix_Music* musicObstacle;
Mix_Music* musicGift;
Mix_Music* newStuffMusic;
bool powerTaken = false;
bool obstacleA = true;
bool obstacleB = true;
bool obstacleC = true;
bool minusLeft = true;
bool minusRight = true;
int moves = 0;
int backgroundShift = 0;
int backgroundShiftRight = 0;
int objectY = 0;
int objectX = 0;
float t = 0.0f;
int res[2] = {0,0};
int obstA[2] = {0,0};
int obstB[2] = {0,0};
int obstC[2] = {0,0};
int powerUpP0[2]= {0,77};
int powerUpP1[2]={100,500};
int powerUpP2[2] = {500,500};
int powerUpP3[2] = {820,145};
//Original coordinates of the first obstacle
int obstacleAP0[2]= {0,0};
int obstacleAP1[2]={100,500};
int obstacleAP2[2] = {500,500};
int obstacleAP3[2] = {810,505.75};
//Original coordinates of the second obstacle
int obstacleBP0[2]= {53,8};
int obstacleBP1[2]={700,14};
int obstacleBP2[2] = {689,596};
int obstacleBP3[2] = {800,352};
//Original coordinates of the third obstacle
int obstacleCP0[2]= {0,18};
int obstacleCP1[2]={700,52};
int obstacleCP2[2] = {700,485};
int obstacleCP3[2] = {810,111};
//-----------------

/*
To run the file you need to have a linux machine with the libraries for Opengl and sdl_mixer downloaded
on it.
The command to run is: 
g++ assignment1.cpp -lSDL2 -lSDL2_mixer  -lglut -lGL -lGLU -lGLEW  -o assignment1 && ./assignment1

*/


//--------------------------------------------------
int main(int argc, char** argr) {
  Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
  musicObstacle = Mix_LoadMUS("obstacle.wav");
  musicGift = Mix_LoadMUS("gift.wav");
  newStuffMusic = Mix_LoadMUS("newStuff.wav");
  glutInit(&argc, argr);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Assignment 1");
  glutDisplayFunc(Display);
  glutIdleFunc(Anim);
  glutSpecialFunc(spe);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  gluOrtho2D(0.0, 800.0, 0.0, 800.0);
  glutMainLoop();
  return 1;
}
void drawStickMan(){
    
  

  //Hat
  glBegin(GL_TRIANGLES); 
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(400.0f, 450.0+32.5f, 0.0f);
  glVertex3f(380.0f, 415.0+32.5f, 0.0f);
  glVertex3f(420.0f, 415.0+32.5f, 0.0f);
  glEnd();
  
  
  
  //Right Arm
  glLineWidth(50.0f);
  glBegin(GL_LINES);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(435.0f, 373.0+32.5f, 0.0f);
  glVertex3f(455.0f,340.0+32.5f,0.0f);
  glEnd();
  //Left Arm
  glBegin(GL_LINES);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(365.0f, 373.0+32.5f, 0.0f);
  glVertex3f(345.0f,340.0+32.5f,0.0f);
  glEnd();
  //Left Leg
  glBegin(GL_POLYGON); 
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(365.0f, 325.0+32.5f, 0.0f);
  glVertex3f(365.0f, 285.0+32.5f, 0.0f);
  glVertex3f(385.0f, 285.0+32.5f, 0.0f);
  glVertex3f(385.0f, 325.0+32.5f, 0.0f);
  glEnd();

  //Left Shoe
  glBegin(GL_POLYGON);
  glColor3f(0.0f, 1.0f, 1.0f);
  glVertex3f(365.0f, 285.0+32.5f, 0.0f);
  glVertex3f(365.0f, 275.0+32.5f, 0.0f);
  glVertex3f(395.0f, 275.0+32.5f, 0.0f);
  glVertex3f(385.0f, 285.0+32.5f, 0.0f);
  glEnd();

  //Right Leg
  glBegin(GL_POLYGON); 
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(435.0f, 325.0+32.5f, 0.0f);
  glVertex3f(435.0f, 285.0+32.5f, 0.0f);
  glVertex3f(415.0f, 285.0+32.5f, 0.0f);
  glVertex3f(415.0f, 325.0+32.5f, 0.0f);
  glEnd();
  //Right Shoe
  glBegin(GL_POLYGON);
  glColor3f(0.0f, 1.0f, 1.0f);
  glVertex3f(415.0f, 285.0+32.5f, 0.0f);
  glVertex3f(415.0f, 275.0+32.5f, 0.0f);
  glVertex3f(445.0f, 275.0+32.5f, 0.0f);
  glVertex3f(435.0f, 285.0+32.5f, 0.0f);
  glEnd();
  
  
  
  
  //Body of the man
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 1.0f, 1.0f); 
  glVertex3f(365.0f, 375.0+32.5f, 0.0f);
  glVertex3f(435.0f, 375.0+32.5f, 0.0f);
  glVertex3f(435.0f, 325.0+32.5f, 0.0f);
  glVertex3f(365.0f, 325.0+32.5f, 0.0f);
  glEnd();
  
  //Circle
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(400, 400+32.5, 0);
  GLUquadric *quadObj = gluNewQuadric();
  gluDisk(quadObj, 0, 25, 50, 50);

  
}
//Belgium Flag
void drawLeftBackGround(){
  //Left-most rectangle
  glBegin(GL_POLYGON);
  glColor3f(0.0f, 0.0f, 0.0f); 
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 800.0f, 0.0f);
  glVertex3f(266.0f, 800.0f, 0.0f);
  glVertex3f(266.0f, 0.0f, 0.0f);
  glEnd();
  //Middle Rectangle
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 0.82f, 0.26f); 
  glVertex3f(266.0f, 0.0f, 0.0f);
  glVertex3f(266.0f, 800.0f, 0.0f);
  glVertex3f(533.0f, 800.0f, 0.0f);
  glVertex3f(533.0f, 0.0f, 0.0f);
  glEnd();
  //Right-most Rectangle
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 0.0f, 0.0f); 
  glVertex3f(533.0f, 0.0f, 0.0f);
  glVertex3f(533.0f, 800.0f, 0.0f);
  glVertex3f(800.0f, 800.0f, 0.0f);
  glVertex3f(800.0f, 0.0f, 0.0f);
  glEnd();
}

//Germany Flag
void drawRightBackGround(){
  //Left-most rectangle
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 0.82f, 0.26f); 
  glVertex3f(0.0+800.0f, 0.0f, 0.0f);
  glVertex3f(0.0+800.0f, 800.0f, 0.0f);
  glVertex3f(266.0+800.0f, 800.0f, 0.0f);
  glVertex3f(266.0+800.0f, 0.0f, 0.0f);
  glEnd();
  //Middle Rectangle
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 0.0f, 0.0f);  
  glVertex3f(266.0+800.0f, 0.0f, 0.0f);
  glVertex3f(266.0+800.0f, 800.0f, 0.0f);
  glVertex3f(533.0+800.0f, 800.0f, 0.0f);
  glVertex3f(533.0+800.0f, 0.0f, 0.0f);
  glEnd();
  //Right-most Rectangle
  glBegin(GL_POLYGON);
  glColor3f(0.0f, 0.0f, 0.0f); 
  glVertex3f(533.0+800.0f, 0.0f, 0.0f);
  glVertex3f(533.0+800.0f, 800.0f, 0.0f);
  glVertex3f(800.0+800.0f, 800.0f, 0.0f);
  glVertex3f(800.0+800.0f, 0.0f, 0.0f);
  glEnd();

}



void drawObstacleA(){
  glBegin(GL_TRIANGLES); 
  glColor3f(0.26f, 0.01f, 0.38f);
  glVertex3f(810.0f, 521.0f, 0.0f);
  glVertex3f(795.0f, 491.0f, 0.0f);
  glVertex3f(825.0f, 491.0f, 0.0f);
  glEnd();
}

void drawObstacleB(){
  glBegin(GL_POLYGON); 
  glColor3f(1.0f, 0.2f, 0.4f);
  glVertex3f(810.0f, 126.0f, 0.0f);
  glVertex3f(825.0f, 111.0f, 0.0f);
  glVertex3f(810.0f, 96.0f, 0.0f);
  glVertex3f(795.0f, 111.0f, 0.0f);
  glEnd();
}

void drawObstacleC(){
  glBegin(GL_TRIANGLES); 
  glColor3f(0.55f, 0.68f, 0.68f);
  glVertex3f(800.0f, 367.0f, 0.0f);
  glVertex3f(785.0f, 337.0f, 0.0f);
  glVertex3f(815.0f, 337.0f, 0.0f);
  glEnd();
}

void drawDestination(){
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(760.0f, 800.0f, 0.0f);
  glVertex3f(775.0f, 800.0f, 0.0f);
  glVertex3f(775.0f, 0.0f, 0.0f);
  glVertex3f(760.0f, 0.0f, 0.0f);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.0f, 0.0f, 0.0f);
  glVertex3f(775.0f, 800.0f, 0.0f);
  glVertex3f(800.0f, 800.0f, 0.0f);
  glVertex3f(800.0f, 0.0f, 0.0f);
  glVertex3f(775.0f, 0.0f, 0.0f);
  glEnd();
  
}


void drawPowerUp(){
  glBegin(GL_POLYGON);
  glColor3f(0.212f, 0.282f, 0.255f); 
  glVertex3f(480.0+330.0f, 400.0-250.0f, 0.0f);
  glVertex3f(500.0+330.0f, 400.0-250.0f, 0.0f);
  glVertex3f(500.0+330.0f, 380.0-250.0f, 0.0f);
  glVertex3f(480.0+330.0f, 380.0-250.0f, 0.0f);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.28f, 0.616f, 0.455f); 
  glVertex3f(475.0+330.0f, 410.0-250.0f, 0.0f);
  glVertex3f(505.0+330.0f, 410.0-250.0f, 0.0f);
  glVertex3f(505.0+330.0f, 400.0-250.0f, 0.0f);
  glVertex3f(475.0+330.0f, 400.0-250.0f, 0.0f);
  glEnd();
};

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glPushMatrix();
  if(minusLeft)
  {
    glTranslated(-backgroundShift,0,0);
  }
  else{
    glTranslated(backgroundShift,0,0);
  }
  drawLeftBackGround();
  glPopMatrix();

  glPushMatrix();
  
  glTranslated(-backgroundShiftRight,0,0);
  drawRightBackGround();
  glPopMatrix();

  if(power && (!powerTaken))
  {
    glPushMatrix();
    glTranslated(-res[0],res[1],0);
    drawPowerUp();
    glPopMatrix();
  }

  if(obstacleA)
  {
    glPushMatrix();
    glTranslated(-obstA[0],-obstA[1],0);
    drawObstacleA();
    glPopMatrix();
  }
  if(obstacleB)
  {
    glPushMatrix();
    glTranslated(-obstB[0],obstB[1],0);
    drawObstacleB();
    glPopMatrix();
  }
  
  if(obstacleC)
  {
    glPushMatrix();
    glTranslated(-obstC[0],obstC[1],0);
    drawObstacleC();
    glPopMatrix();
  }


  glPushMatrix();
  glTranslated(objectX,objectY,0);
  drawStickMan();
  glPopMatrix();

  glPushMatrix();
  drawDestination();
  glPopMatrix();
  
  glFlush();
}
void spe(int k, int x, int y)
{// int k: is the special key pressed such as the keyboard arrows the f1,2,3 and so on
  if ((k == GLUT_KEY_UP) && (objectY < 297.5) )//if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
    objectY += 10;
  if ((k == GLUT_KEY_DOWN) && (objectY > -297.5))//if the down arrow is pressed, then the object will be translated in the y axis by -10. (moving downwords)
    objectY -= 10;

glutPostRedisplay();//redisplay to update the screen with the changes
}
//Moving the Charachter forward
void checkPowerUp(){
  if(!power || powerTaken)
    return;
  if((805-res[0] <= 455+objectX) && (805-res[0] >= 345+objectX))
  {
    if((160+res[1] <= 482.5+objectY) && (160+res[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicGift,0);
      objectX +=120;
      moves += 1;
      powerTaken = true;
    }
    else if ((130+res[1] <= 482.5+objectY) && (130+res[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicGift,0);
      objectX +=120;
      moves += 1;
      powerTaken = true;
    }
  }

}

void checkObstacleA(){
  if(!obstacleA)
    return;
  if((795-obstA[0] <= 455+objectX) && (795-obstA[0] >= 345+objectX))
  {
    if((521-obstA[1] <= 482.5+objectY) && (521-obstA[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicObstacle,0);
      objectX -=120;
      moves -= 1;
      obstacleA = false;
    }
    else if ((491-obstA[1] <= 482.5+objectY) && (491-obstA[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicObstacle,0);
      objectX -=120;
      moves -= 1;
      obstacleA = false;
    }
  }
 }

 void checkObstacleB(){
  if(!obstacleB)
    return;
  if((795-obstB[0] <= 455+objectX) && (795-obstB[0] >= 345+objectX))
  {
    if((126+obstB[1] <= 482.5+objectY) && (126+obstB[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicObstacle,0);
      objectX -=120;
      moves -= 1;
      obstacleB = false;
    }
    else if ((96+obstB[1] <= 482.5+objectY) && (96+obstB[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicObstacle,0);
      objectX -=120;
      moves -= 1;
      obstacleB = false;
    }
  }
 }

 void checkObstacleC(){
  if(!obstacleC)
    return;
  if((785-obstC[0] <= 455+objectX) && (785-obstC[0] >= 345+objectX))
  {
    if((367+obstC[1] <= 482.5+objectY) && (367+obstC[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicObstacle,0);
      objectX -=120;
      moves -= 1;
      obstacleC = false;
    }
    else if ((337+obstC[1] <= 482.5+objectY) && (337+obstC[1] >= 307.5+objectY) )
    {
      Mix_PlayMusic(musicObstacle,0);
      objectX -=120;
      moves -= 1;
      obstacleC = false;
    }
  }
 }

 

void Anim()
{ 
  int x;
  bool y;
  
  checkPowerUp();
  checkObstacleA();
  checkObstacleB();
  checkObstacleC();
  if(moves == -3 )
  {
    for(int i = 0; i < 1000000000; i++);
    bringEveryThingBack();
    glutPostRedisplay();
    return;
  }
  if(moves == 3)
  {
    for(int i = 0; i < 1000000000; i++);
    bringEveryThingBack();
    glutPostRedisplay();
    return;

  }
  if(t<1)
  {
    if(power && (!powerTaken))
    {
      //To enable powerUp appearance with the obstacles
      res[0]=pow((1-t),3)*powerUpP0[0]+3*t*pow((1-t),2)*powerUpP1[0]+3*pow(t,2)*(1-t)*powerUpP2[0]+pow(t,3)*powerUpP3[0];
      res[1]=pow((1-t),3)*powerUpP0[1]+3*t*pow((1-t),2)*powerUpP1[1]+3*pow(t,2)*(1-t)*powerUpP2[1]+pow(t,3)*powerUpP3[1];
    }
    if(obstacleA)
    {
      obstA[0] =pow((1-t),3)*obstacleAP0[0]+3*t*pow((1-t),2)*obstacleAP1[0]+3*pow(t,2)*(1-t)*obstacleAP2[0]+pow(t,3)*obstacleAP3[0];
      obstA[1] =pow((1-t),3)*obstacleAP0[1]+3*t*pow((1-t),2)*obstacleAP1[1]+3*pow(t,2)*(1-t)*obstacleAP2[1]+pow(t,3)*obstacleAP3[1];
    }
    if(obstacleB)
    {
      obstB[0] =pow((1-t),3)*obstacleBP0[0]+3*t*pow((1-t),2)*obstacleBP1[0]+3*pow(t,2)*(1-t)*obstacleBP2[0]+pow(t,3)*obstacleBP3[0];
      obstB[1] =pow((1-t),3)*obstacleBP0[1]+3*t*pow((1-t),2)*obstacleBP1[1]+3*pow(t,2)*(1-t)*obstacleBP2[1]+pow(t,3)*obstacleBP3[1];
    }
    if(obstacleC)
    {
      obstC[0] =pow((1-t),3)*obstacleCP0[0]+3*t*pow((1-t),2)*obstacleCP1[0]+3*pow(t,2)*(1-t)*obstacleCP2[0]+pow(t,3)*obstacleCP3[0];
      obstC[1] =pow((1-t),3)*obstacleCP0[1]+3*t*pow((1-t),2)*obstacleCP1[1]+3*pow(t,2)*(1-t)*obstacleCP2[1]+pow(t,3)*obstacleCP3[1];
    }
    
    t += 0.001;
  }
  else{
    Mix_PlayMusic(newStuffMusic,0);
    t = 0.0f;
    x = moves;
    y = !power;
    power = !power;
    powerTaken= false;
    obstacleA = true;
    obstacleB = true;
    obstacleC = true;
    res[0] = 0;
    res[1] = 0;
    obstA[0] = 0;
    obstA[1] = 0;
    obstB[0] = 0;
    obstB[1] = 0;
    obstC[0] = 0;
    obstC[1] = 0;
  }

  if(minusLeft)
  {
    if(backgroundShift >= 800)
    {
      minusLeft = false;
    }
    else{
      backgroundShift += 1;
    }
  }
  else if(!minusLeft)
  {
    if(backgroundShift <= 0)
    {
      minusLeft = true;
    }
    else{
      backgroundShift -= 1;
    }
  }
 
  if(backgroundShiftRight >= 1600)
  {
    minusRight  = false;
    backgroundShiftRight = 0;
  }
  else{
    backgroundShiftRight += 1;
  }
 
  for(int i = 0; i < 4000000; i++);
	glutPostRedisplay();
}

void bringEveryThingBack(){
  power = false;
  powerTaken = false;
  obstacleA = true;
  obstacleB = true;
  obstacleC = true;
  minusLeft = true;
  minusRight = true;
  moves = 0;
  backgroundShift = 0;
  backgroundShiftRight = 0;
  objectY = 0;
  objectX = 0;
  t = 0.0f;
  res[0] = 0;
  res[1] = 0;
  obstA[0] = 0;
  obstA[1] = 0;
  obstB[0] = 0;
  obstB[1] = 0;
  obstC[0] = 0;
  obstC[1] = 0;
}