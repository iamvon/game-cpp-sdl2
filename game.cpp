#include "game.h"

#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

int randomNumber(int minNum, int maxNum) {
  return rand()%(maxNum - minNum + 1) + minNum;
}

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren);
  SDL_SetWindowTitle(win, "My game");

  TTF_Init();
  running=true; error = 32,aError = -33; checkPos = false, loser = false, play = false; checkRepair = false;
  kmCounter = 0, healthAmount = 5; goal = 2000; checkCollision = false; countCollision = 0;
  x = WIDTH/2 - SHIP_SIZE_W/2; y = HEIGHT - SHIP_SIZE_H - 250;
  xBg_1 = 0, yBg_1 = 0, xBg_2 = 0, yBg_2 = -HEIGHT;
  xRe = randomNumber(0, WIDTH - HEALTH_SIZE*4), yRe = -HEALTH_SIZE*10;
  xA_1 = randomNumber(0, WIDTH - ASTEROID_SIZE/2), yA_1 = -SHIP_SIZE_H;
  reWidth = HEALTH_SIZE*2.4; reHeight = HEALTH_SIZE*2;
  angle = 0, aScale = randomNumber(2,5);
  font = TTF_OpenFont("assets/Digital_tech.otf", FONT_SIZE);

// ================================== INIT SPRITE ENTITY ===================================== //  
   ship.setImage("assets/ship.png",ren);
   ship_1 = ship.createCycle(1, 512, 512, 4, 8);
   ship.setCurAnimation(ship_1);

   explosion.setImage("assets/explosion.png",ren);
   explosion_1 = explosion.createCycle(1, 118, 118, 5, 14);
   explosion.setCurAnimation(explosion_1);

// ================================== INIT OBJECTS ===================================== //
  for (int i = 0; i < healthAmount; ++i) {
  health[i].setSource(0, 0, 1200, 1200);
  health[i].setImage("assets/heart.png", ren);
  }

  asteroid1.setSource(0, 0, ASTEROID_SIZE, ASTEROID_SIZE);
  asteroid1.setImage("assets/asteroid-3.png", ren);

  bg1.setSource(0, 0, 1080, 1280);
  bg1.setImage("assets/bg-10.jpg", ren);

  bg2.setSource(0, 0, 1080, 1920);
  bg2.setImage("assets/bg-10.jpg", ren);

  gameover.setSource(0, 0, WIDTH, HEIGHT);
  gameover.setImage("assets/gameover3.png", ren);

  start.setSource(0, 0, WIDTH, HEIGHT);
  start.setImage("assets/start.png", ren);
  start.setDest(0, 0, WIDTH, HEIGHT);

  repair.setSource(0, 0, 417, 330);
  repair.setImage("assets/repair.png", ren);

  loop();
}

Game::~Game() {
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

void Game::loop() {
  while(running) {

    lastFrame=SDL_GetTicks();
    static int lastTime;
    if(lastFrame >= (lastTime + SHIP_SPEED)) {
      lastTime=lastFrame;
      frameCount=0;
     if (loser == false && play == true) {
         kmCounter += 1;   //  increase km
       }
    }

// ==================================   UPDATE BACKGROUND'S STATE ===================================== //
// scrolling background
  if (yBg_1 >= HEIGHT) {
     yBg_1 = 0;
     yBg_2 = -HEIGHT;
  }
   //  move background
  if (loser == false) {
   bg1.setDest(xBg_1, yBg_1, WIDTH, HEIGHT); yBg_1+=1.4; 
   bg2.setDest(xBg_2, yBg_2, WIDTH, HEIGHT); yBg_2+=1.4; 
  }
  else {
   bg1.setDest(xBg_1, yBg_1, WIDTH, HEIGHT); yBg_1+=0.25;
   bg2.setDest(xBg_2, yBg_2, WIDTH, HEIGHT); yBg_2+=0.25;
  }

// ==================================   UPDATE ASTEROID'S STATE ===================================== //

// repeat random asteroid1
  if (yA_1 >= HEIGHT || collision(x, y, xA_1, yA_1))  {
    if (collision(x, y, xA_1, yA_1)){
      checkCollision = true;   // kiểm tra sự kiện va chạm thật
    } 
    xA_1 = randomNumber(0, WIDTH);
    yA_1 = -SHIP_SIZE_H;
    aScale = randomNumber(2,5);
    step = randomNumber(1,5);
   if(xA_1 <= WIDTH/2) checkPos = true; else checkPos = false;
  }

  // move asteroid1
   aWidth = ASTEROID_SIZE/aScale; aHeight = ASTEROID_SIZE/aScale;
   asteroid1.setDest(xA_1, yA_1, aWidth, aHeight);
   if (play == true) {
      if(checkPos) {
       xA_1 += 1/step; yA_1 += 3; angle += 2;
     }
      else {
       xA_1 -= 1/step; yA_1 += 3; angle += 2;
     }
   }


  //  explosion.setDest(x, y, 0, 0);
  //  if(collision(x, y, xA_1, yA_1)) {
  //     cout << "collision" << endl;
  //     //  cout << countcollision << endl;
  //  } else cout << "not collision" << endl;

// ==================================   UPDATE COLLISION'S STATE ===================================== //
  // xử lý vụ nổ va chạm
    if(checkCollision){
      explosion.setDest(x, y-20, 170, 170); 
      ++countCollision;
      if(countCollision >= 80)  {   // kéo dài tgian cho hiệu ứng nổ
        checkCollision = false; countCollision = 0; 
        }
    }   else explosion.setDest(x, y, 0, 0); 
  
// ==================================   UPDATE REPAIR'S STATE ===================================== //  
  // repeat repair
  if(yRe >= HEIGHT+HEALTH_SIZE*4 || repairCollision(x, y, xRe, yRe)) { 
    if (repairCollision(x, y, xRe, yRe)) {
      checkRepair = true;  //  kiểm tra sự kiện repair thật
    } else checkRepair = false;
    xRe = randomNumber(0, WIDTH - HEALTH_SIZE*4), yRe = -HEALTH_SIZE*10;
  }
   if(play == true && loser == false && healthAmount <= 3) {  // điều kiện xuất hiện repair
      repair.setDest(xRe, yRe, reWidth, reHeight); yRe+=1;
   } 


  //   cout << x << " | " << xA_1 << endl;
  //   cout << y << " | " << yA_1 << endl;
  //  cout << mouseX << " | " << mouseY << endl;

 
// ==================================   UPDATE SHIP'S STATE ===================================== //
   // ship bottom border
   if(y > HEIGHT-SHIP_SIZE_H-20) y = HEIGHT-SHIP_SIZE_H-20;
   ship.setDest(x, y, SHIP_SIZE_W, SHIP_SIZE_H); 
   if (y != HEIGHT-SHIP_SIZE_H-20) y += 0.3;   // move ship backward

   // update ship's health
   for (int i = 0; i < healthAmount; ++i) {
    if(collision(x, y, xA_1, yA_1)) { 
      --healthAmount; 
       break;
       } 
    if(checkRepair == true) {
      if (healthAmount < 5) {
        ++healthAmount;  
      }
       checkRepair = false;
    }  
    health[i].setDest(WIDTH - 35 - i*35, HEIGHT - 35, HEALTH_SIZE, HEALTH_SIZE);
  }

   
   gameover.setDest(0, 0, WIDTH, HEIGHT);  // Game Over

    render();
    input();
    update();
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(ren, 126, 192, 238, 255);
  SDL_Rect rect;
  rect.x=rect.y=0;
  rect.w=WIDTH;
  rect.h=HEIGHT;
  SDL_RenderFillRect(ren, &rect);

   draw(bg1);
   draw(bg2);
  drawSpin(asteroid1, angle);

  draw(repair);

  stringstream ss;
  ss << goal - kmCounter;
  string ssKm = ss.str();
  const char* km = ssKm.c_str();

  drawMsg(km, 70, 80, 234, 123, 123);
  drawMsg("KM", 140, 80, 234, 123, 123);

   // update ship's health
  for(int i = 0; i < healthAmount; ++i) {
   draw(health[i]);
  }

  draw(ship);
  draw(explosion);

  if(play == false) draw(start);

  if(healthAmount == 0) {
    loser = true;
    draw(gameover);
  }
  
  frameCount++;
  int timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(BACKGROUND_SPEED/FPS)) {
    SDL_Delay((BACKGROUND_SPEED/FPS)-timerFPS);
  }

  SDL_RenderPresent(ren);

}

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {

    // Choose menu
    if(e.type == SDL_MOUSEBUTTONDOWN) {
       if((234 <= mouseX && mouseX <= 346) && (360 <= mouseY && mouseY <= 432)) play = true;
       else if((234 <= mouseX && mouseX <= 346) && (489 <= mouseY && mouseY <= 561))  running = false;
    }

    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}
    if(e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_ESCAPE) running=false;

      // di chuyển và bo viền
      if (loser == false) {
        if(0 >= x+10) x = -15; if(x > WIDTH-SHIP_SIZE_W+10) x = WIDTH-SHIP_SIZE_W+10;
        if(0 >= y+10) y = -15;

        if(e.key.keysym.sym == SDLK_LEFT) x -= SHIP_SPEED_MOVE, y -= 3;
        else if(e.key.keysym.sym == SDLK_RIGHT) x += SHIP_SPEED_MOVE, y -= 3;
        else if (e.key.keysym.sym == SDLK_UP)  y -= 4;
        else if (e.key.keysym.sym == SDLK_DOWN)  y += 1;

        else if (e.key.keysym.sym == SDLK_UP) {
          if (e.key.keysym.sym == SDLK_LEFT)  x -= SHIP_SPEED_MOVE, y -= 4;
        } 
        else if (e.key.keysym.sym == SDLK_UP) {
          if(e.key.keysym.sym == SDLK_RIGHT)  x += SHIP_SPEED_MOVE, y -= 4;
        } 
        else if (e.key.keysym.sym ==  SDLK_LEFT) {
          if (e.key.keysym.sym == SDLK_UP)  x -= SHIP_SPEED_MOVE, y -= 4;
        }
        else if (e.key.keysym.sym == SDLK_RIGHT) {
          if(e.key.keysym.sym == SDLK_UP)  x += SHIP_SPEED_MOVE, y -= 4;
        }
      }
    }
     if(e.type == SDL_KEYUP) {
        //  if(e.key.keysym.sym == SDLK_LEFT && (0 <= x && x <= WIDTH-SHIP_SIZE_W)) x += 0;
        //  else if(e.key.keysym.sym == SDLK_RIGHT && (0 <= x && x <= WIDTH-SHIP_SIZE_W)) x -= 0;
     }
     SDL_GetMouseState(&mouseX, &mouseY);
  }
}

//  update sprite
void Game::update() {
   ship.updateAnimation();
   explosion.updateAnimation();
}

// ==================================== Collision Logic ===================================================== //

bool Game::collision(double x, double y, double xA_1, double yA_1) {
  // cout << aWidth << ' ' << aHeight << endl;
  if ((x+error <= xA_1 && xA_1 <= x+SHIP_SIZE_W-error) && (y+error <= yA_1+aError && yA_1+aError <= y+SHIP_SIZE_H-110)) return true;
  else if ((x+error <= xA_1+aWidth && xA_1+aWidth <= x+SHIP_SIZE_W-error) && (y+error <= yA_1+aError && yA_1+aError <= y+SHIP_SIZE_H-110)) return true;
  else if ((x+error <= xA_1+aWidth && xA_1+aWidth <= x+SHIP_SIZE_W-error) && (y+error <= yA_1+aHeight+aError && yA_1+aHeight+aError <= y+SHIP_SIZE_H-110)) return true;
  else if ((x+error <= xA_1 && xA_1 <= x+SHIP_SIZE_W-error) && (y+error <= yA_1+aHeight+aError && yA_1+aHeight+aError <= y+SHIP_SIZE_H-110)) return true;
  else return false;
}

bool Game::repairCollision(double x, double y, double xRe, double yRe) {
  if ((x+error <= xRe && xRe <= x+SHIP_SIZE_W-error) && (y+error <= yRe && yRe <= y+SHIP_SIZE_H-50)) return true;
  else if ((x+error <= xRe+reWidth && xRe+reWidth <= x+SHIP_SIZE_W-error) && (y+error <= yRe && yRe <= y+SHIP_SIZE_H-50)) return true;
  else if ((x+error <= xRe+reWidth && xRe+reWidth <= x+SHIP_SIZE_W-error) && (y+error <= yRe+reHeight && yRe+reHeight <= y+SHIP_SIZE_H-50)) return true;
  else if ((x+error <= xRe && xRe <= x+SHIP_SIZE_W-error) && (y+error <= yRe+reHeight && yRe+reHeight <= y+SHIP_SIZE_H-50)) return true;
  else return false;
}


// ==================================== Draw functions ===================================================== //

void Game::draw(Object obj) {
 SDL_Rect dest = obj.getDest();
 SDL_Rect src = obj.getSource();
 SDL_RenderCopyEx(ren, obj.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void Game::drawSpin(Object obj, int angle) {
//  angle = 0;
 SDL_Rect dest = obj.getDest();
 SDL_Rect src = obj.getSource();
 SDL_RenderCopyEx(ren, obj.getTex(), &src, &dest, angle, NULL, SDL_FLIP_NONE);
}

void Game::drawMsg(const char* msg, int x, int y, int r, int g, int b) {
 SDL_Surface* surf;
 SDL_Texture* tex;
 SDL_Color color;
 color.r=r;
 color.g=g;
 color.b=b;
 color.a=255;
 SDL_Rect rect;
 surf = TTF_RenderText_Solid(font, msg, color);
 tex = SDL_CreateTextureFromSurface(ren, surf);
 rect.x=x;
 rect.y=y;
 rect.w=surf->w;
 rect.h=surf->h;
 SDL_FreeSurface(surf);
 SDL_RenderCopy(ren, tex, NULL, &rect);
 SDL_DestroyTexture(tex);
}
