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
  SDL_SetWindowTitle(win, "Return to Earth");

  TTF_Init();
  running=true; error = 31,aError = -30; checkPos1 = false, loser = false, play = false; checkRepair = false; countShootingConllision = 0; shooting= false; checkBulletBuff = false; checkBulletBuff1 = false;
  kmCounter = 0, healthAmount = 5; fireAmount = 27; goal = 2000; checkCollision1 = false; checkCollision2 = false; countCollision1 = 0, countCollision2 = 0; countShooting = 1;
  x = WIDTH/2 - SHIP_SIZE_W/2; y = HEIGHT - SHIP_SIZE_H - 250;
  xBg_1 = 0, yBg_1 = 0, xBg_2 = 0, yBg_2 = -HEIGHT;
  xRe = randomNumber(0, WIDTH - HEALTH_SIZE*4), yRe = -HEALTH_SIZE*10;
  xBulletBuff = randomNumber(0, WIDTH - BULLET_BUFF_SIZE), yBulletBuff = -BULLET_BUFF_SIZE*5;
  xA_1 = randomNumber(0, WIDTH - ASTEROID_SIZE/2), yA_1 = -SHIP_SIZE_H;
  xA_2 = randomNumber(0, WIDTH - ASTEROID_SIZE/2), yA_2 = -SHIP_SIZE_H-100;
  xWormHole = 200, yWormHole = 350;
  shipWidth = SHIP_SIZE_W, shipHeight = SHIP_SIZE_H;
  for(int i = 1; i < fireAmount; ++i) {
    xFire[i] = x+SHIP_SIZE_W/2-47, yFire[i] = y+50;
    fireWidth[i] = 56, fireHeight[i] = 56;
  }
  fireScale = 0, offset=48;
  reWidth = HEALTH_SIZE*2.4; reHeight = HEALTH_SIZE*2;
  angle = 0, aScale1 = randomNumber(2,5);
  holeAngle = 0;
  font = TTF_OpenFont("assets/Digital_tech.otf", FONT_SIZE);

// ================================== INIT SPRITE ENTITY ===================================== //
   ship.setImage("assets/ship.png",ren);
   ship_1 = ship.createCycle(1, 512, 512, 4, 8);
   ship.setCurAnimation(ship_1);

   explosion.setImage("assets/explosion.png",ren);
   explosion_1 = explosion.createCycle(1, 118, 118, 5, 14);
   explosion.setCurAnimation(explosion_1);

   blue.setImage("assets/blue.png",ren);
   blue.setDest(200, 200, 150, 150);
   blue_1 = blue.createCycle(1, 256, 256, 17, 10);
   blue.setCurAnimation(blue_1);

//  for(int i = 0; i < fireAmount; ++i) {
//       fire[i].setImage("assets/fireball.png",ren);
//       fire_1[i] = fire[i].createCycle(1, 512, 512, 6, 13);
//       fire[i].setCurAnimation(fire_1[i]);
//    }

// ================================== INIT OBJECTS ===================================== //
  for (int i = 0; i < healthAmount; ++i) {
  health[i].setSource(0, 0, 1200, 1200);
  health[i].setImage("assets/heart.png", ren);
  }

  asteroid1.setSource(0, 0, ASTEROID_SIZE, ASTEROID_SIZE);
  asteroid1.setImage("assets/asteroid-3.png", ren);

  asteroid2.setSource(0, 0, ASTEROID_SIZE, ASTEROID_SIZE);
  asteroid2.setImage("assets/asteroid-4.png", ren);

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

  for(int i = 0; i < fireAmount; ++i) {
     fire[i].setSource(0, 0, 400, 400);
     fire[i].setImage("assets/bullet.png",ren);
   }

  bulletCur.setSource(0, 0, 400, 400);
  bulletCur.setImage("assets/bullet.png", ren);
  bulletCur.setDest(15, HEIGHT - 48, 43, 43);

  wormHole.setSource(0, 0, 750, 750);
  wormHole.setImage("assets/hole.png", ren);
  wormHole.setDest(xWormHole, yWormHole, WORM_HOLE_SIZE, WORM_HOLE_SIZE);

  board.setSource(0, 0, 300, 330);
  board.setImage("assets/gear4.png", ren);
  board.setDest(25, 30, 130, 143);

  bulletBuff.setSource(0, 0, 400, 400);
  bulletBuff.setImage("assets/bulletBuff1.png", ren);

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
    if(holeAngle > 10000000) holeAngle = 4;
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
  if (yA_1 >= HEIGHT || collision(x, y, xA_1, yA_1, aWidth1, aHeight1))  {
    if (collision(x, y, xA_1, yA_1, aWidth1, aHeight1)){
      xA_1Last = xA_1, yA_1Last = yA_1;
      checkCollision1 = true;   // kiểm tra sự kiện va chạm thật
    }
    resetAsteroid1(xA_1, yA_1, aScale1, step1);
  }

  // move asteroid1
   aWidth1 = ASTEROID_SIZE/aScale1; aHeight1 = ASTEROID_SIZE/aScale1;
   asteroid1.setDest(xA_1, yA_1, aWidth1, aHeight1);
   if (play == true) {
      if(checkPos1) {
       xA_1 += 1/step1; yA_1 += 3; angle += 2;
     }
      else {
       xA_1 -= 1/step1; yA_1 += 3; angle += 2;
     }
   }

  // repeat random asteroid2
  if (yA_2 >= HEIGHT || collision(x, y, xA_2, yA_2, aWidth2, aHeight2))  {
    if (collision(x, y, xA_2, yA_2, aWidth2, aHeight2)){
      // xA_1Last = xA_1, yA_1Last = yA_1;
       checkCollision2 = true;   // kiểm tra sự kiện va chạm thật
    }
    resetAsteroid2(xA_2, yA_2, aScale2, step2);
  }

  // move asteroid2
   aWidth2 = ASTEROID_SIZE/aScale2; aHeight2 = ASTEROID_SIZE/aScale2;
   asteroid2.setDest(xA_2, yA_2, aWidth2, aHeight2);
   if (play == true) {
      if(checkPos2) {
       xA_2 += 1/step2; yA_2 += 3; angle += 2;
     }
      else {
       xA_2 -= 1/step2; yA_2 += 3; angle += 2;
     }
   }

// ==================================   UPDATE SHOOTING'S STATE ====================================== //
 if(checkBulletBuff == true && countShooting == 26)  countShooting = 1, checkBulletBuff = false, checkBulletBuff1 = true; // Bullet buff
 else checkBulletBuff1 = false;
  if(yFire[fireAmount-1] >= -fireHeight[fireAmount-1]) {
  if (countShooting < fireAmount) {
    for(int i = 1; i < countShooting; ++i) {
        //  bullet buff

       if(shootingCollision(xFire[i], yFire[i], fireWidth[i], fireHeight[i], xA_1, yA_1, aWidth1, aHeight1) == true || shootingCollision(xFire[i], yFire[i], fireWidth[i], fireHeight[i], xA_2, yA_2, aWidth2, aHeight2) == true) {
        cout << "BOOOOOOOOOOOOOOM" << endl;
        blue.setDest(xFire[i]-50, yFire[i]-70, 150, 150);  //  Explosion effect
        if(shootingCollision(xFire[i], yFire[i], fireWidth[i], fireHeight[i], xA_1, yA_1, aWidth1, aHeight1) == true)   resetAsteroid1(xA_1, yA_1, aScale1, step1);  // Destroy the asteroid1
        if(shootingCollision(xFire[i], yFire[i], fireWidth[i], fireHeight[i], xA_2, yA_2, aWidth2, aHeight2) == true)   resetAsteroid2(xA_2, yA_2, aScale2, step2);  // Destroy the asteroid2
         xFire[i] = -300, yFire[i] = HEIGHT+100;   // Remove bullet
        } else  {
           blue.setDest(xFire[i]-50, yFire[i]-70, 0, 0);
           yFire[i]-=4;
           fire[i].setDest(xFire[i], yFire[i], fireWidth[i], fireHeight[i]);
        }

      //  cout << xFire[i]  << " | " << yFire[i] << endl;
     }
    // cout << countShooting << endl;
   } else  blue.setDest(xLast, yLast, 0, 0);

  }
// ==================================   UPDATE COLLISION'S STATE ===================================== //
  // xử lý vụ nổ va chạm
    if(checkCollision1 || checkCollision2){
      if(checkCollision1) {
        explosion.setDest(x-5, y-25, 190, 190);
      ++countCollision1;
      if(countCollision1 >= 60)  {   // kéo dài tgian cho hiệu ứng nổ
        checkCollision1 = false; countCollision1 = 0;
        }
      }
      if(checkCollision2){
      explosion.setDest(x-5, y-25, 190, 190);
      ++countCollision2;
      if(countCollision2 >= 60)  {   // kéo dài tgian cho hiệu ứng nổ
        checkCollision2 = false; countCollision2 = 0;
        }
    }
    } else explosion.setDest(x, y, 0, 0);


// ==================================   UPDATE BUFF'S STATE ===================================== //
  // repeat repair
  if(yRe >= HEIGHT+HEALTH_SIZE*4 || buffCollision(x, y, xRe, yRe)) {
    if (buffCollision(x, y, xRe, yRe)) {
      checkRepair = true;  //  kiểm tra sự kiện repair thật
    } else checkRepair = false;
    xRe = randomNumber(0, WIDTH - HEALTH_SIZE*4), yRe = -HEALTH_SIZE*10;
  }
   if(play == true && loser == false && healthAmount <= 3) {  // điều kiện xuất hiện repair
      repair.setDest(xRe, yRe, reWidth, reHeight); yRe+=1;
   }

    // repeat bullet buff
  if(yBulletBuff >= HEIGHT+BULLET_BUFF_SIZE*2 || buffCollision(x, y, xBulletBuff, yBulletBuff)) {
    if (buffCollision(x, y, xBulletBuff, yBulletBuff)) {
      checkBulletBuff = true;  //  kiểm tra sự kiện bullet buff thật
    } else checkBulletBuff = false;
    xBulletBuff = randomNumber(0, WIDTH - BULLET_BUFF_SIZE), yBulletBuff = -BULLET_BUFF_SIZE*5;
  }
   if(play == true && loser == false && countShooting == 26) {  // điều kiện xuất hiện bullet buff
      bulletBuff.setDest(xBulletBuff, yBulletBuff, BULLET_BUFF_SIZE, BULLET_BUFF_SIZE); yBulletBuff+=1;
   }


// ==================================   UPDATE SHIP'S STATE ===================================== //
   // ship bottom border
   if(y > HEIGHT-SHIP_SIZE_H-20) y = HEIGHT-SHIP_SIZE_H-20;
   ship.setDest(x, y, shipWidth, shipHeight);
   if (y != HEIGHT-SHIP_SIZE_H-20) y += 0.3;   // move ship backward

   // update ship's health
   for (int i = 0; i < healthAmount; ++i) {
    if(collision(x, y, xA_1, yA_1, aWidth1, aHeight1) || collision(x, y, xA_2, yA_2, aWidth2, aHeight2)) {
      // --healthAmount;
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

  // ==================================  UPDATE WORMHOLE'S STATE ===================================== //
  holeAngle+=4;
  // if((x+30 <= xWormHole+WORM_HOLE_SIZE/2 && xWormHole+WORM_HOLE_SIZE/2 <= x+SHIP_SIZE_W-30) && (y+30 <= yWormHole+WORM_HOLE_SIZE/2 && yWormHole+WORM_HOLE_SIZE/2 <= y+SHIP_SIZE_H-30)) {
  //   // x = randomNumber(SHIP_SIZE_W, WIDTH-SHIP_SIZE_W);
  //   // y = randomNumber(SHIP_SIZE_H, HEIGHT-SHIP_SIZE_H);
  //    int i = 7, widthALt = shipWidth, heightAlt = shipHeight;
  //       // while (width != 1 || height != 1) {
  //         shipWidth = widthALt/i, shipHeight = heightAlt/i;
  //         i+=1;
  // }

   wormHoleTeleportShip(ship, x, y, shipWidth, shipHeight, xWormHole, yWormHole);
  
  // if((xA_1 <= xWormHole+WORM_HOLE_SIZE/2 && xWormHole+WORM_HOLE_SIZE/2 <= xA_1+aWidth1) && (yA_1 <= yWormHole+WORM_HOLE_SIZE/2 && yWormHole+WORM_HOLE_SIZE/2 <= yA_1+aHeight1)) {
  //   xA_1 = randomNumber(0, WIDTH-aWidth1);
  //   yA_1 = randomNumber(yWormHole, HEIGHT-aHeight1);
  // }

  // if((xA_2 <= xWormHole+WORM_HOLE_SIZE/2 && xWormHole+WORM_HOLE_SIZE/2 <= xA_2+aWidth2) && (yA_2 <= yWormHole+WORM_HOLE_SIZE/2 && yWormHole+WORM_HOLE_SIZE/2 <= yA_2+aHeight2)) {
  //   xA_2 = randomNumber(0, WIDTH-aWidth2);
  //   yA_2 = randomNumber(yWormHole, HEIGHT-aHeight2);
  // } 
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
  drawSpin(asteroid2, angle);

  draw(repair);
  drawSpin(bulletBuff, 0);

  if(yFire[fireAmount-1] >= -fireHeight[fireAmount-1]) {
    if(countShooting < fireAmount) {
     for(int i = 1; i < countShooting; ++i) {
       if (yFire[i] >= -fireHeight[i]) {
         drawSpin(fire[i], angle);
       }
     }
   }
  }

  draw(ship);
  draw(board);

  stringstream ss, ssBullet;
  ss << goal - kmCounter;
  string ssKm = ss.str();
  const char* km = ssKm.c_str();

  ssBullet << fireAmount - countShooting - 1;
  string ssBulletStr = ssBullet.str();
  const char* bullet = ssBulletStr.c_str();

  drawMsg(bullet, 65, HEIGHT - 40, 234, 123, 123);
  drawMsg(km, 38, 75, 234, 123, 123);
  drawMsg("KM", 108, 75, 234, 123, 123);
  if (checkBulletBuff1 == true)  drawMsg("25 bullets", x+SHIP_SIZE_W/2, y-60, 234, 123, 123);

  // cout << mouseX << " | " << mouseY << endl;
  // cout << km << endl;

   // update ship's health
  for(int i = 0; i < healthAmount; ++i) {
   draw(health[i]);
  }

  if(checkCollision1 == true || checkCollision2 == true)  draw(explosion);
  drawSpin(bulletCur, 0);
  draw(blue);
  drawSpin(wormHole, holeAngle);

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
    // if(e.type == SDL_KEYDOWN) {
    //   if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
    //   if(countShooting < fireAmount-1) {  // chặn spam space
    //      if(e.key.keysym.sym == SDLK_SPACE){
    //         ++countShooting;
    //       xLast = x, yLast = y;
    //         xFire[countShooting-1] = xLast + SHIP_SIZE_W/2-32, yFire[countShooting-1] = yLast+50;  // xử lý vị trí đạn mới tách khỏi tàu
    //         // blue.setDest(xLast, yLast, 150, 150);
    //         // SDL_Delay(1000000);
    //   }
    // }

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
        switch( e.key.keysym.sym ) {
            case SDLK_ESCAPE: running=false; 
            case SDLK_SPACE: 
            if(countShooting < fireAmount-1) {  // chặn spam space
              ++countShooting;
              xLast = x, yLast = y;
              xFire[countShooting-1] = xLast + SHIP_SIZE_W/2-32, yFire[countShooting-1] = yLast+50;  // xử lý vị trí đạn mới tách khỏi tàu 
            }; break;
            case SDLK_UP: yVel -= SHIP_VEL; break;
            case SDLK_DOWN: yVel += SHIP_VEL; break;
            case SDLK_LEFT: xVel -= SHIP_VEL; break;
            case SDLK_RIGHT: xVel += SHIP_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP: yVel += SHIP_VEL; break;
            case SDLK_DOWN: yVel -= SHIP_VEL; break;
            case SDLK_LEFT: xVel += SHIP_VEL; break;
            case SDLK_RIGHT: xVel -= SHIP_VEL; break;
        }
    }
    SDL_GetMouseState(&mouseX, &mouseY);
   }

    // Move the ship left or right
    x += xVel;
    // Bo viền 2 bên
    if(( x < 0 ) || ( x + SHIP_SIZE_W > WIDTH )){
        // Move back
        x -= xVel;
    }
    // Move the ship up or down
    y += yVel;
    // Bo viền trên dưới 
    if(( y < 0 ) || ( y + SHIP_SIZE_H > HEIGHT )) {
        //Move back
        y -= yVel;
    }
  }

// ==================================== Update Sprite ======================================================= //
void Game::update() {
   ship.updateAnimation();
   explosion.updateAnimation();
   blue.updateAnimation();
  // if(countShooting < fireAmount) {
  //   for(int i = 0; i < countShooting; ++i) {
  //     if (yFire[i] >= -fireHeight[i]) {
  //       fire[i].updateAnimation();
  //     }
  //   }
  // }
}

// ==================================== Collision Logic ===================================================== //

bool Game::collision(double x, double y, double xA, double yA, double aWidth, double aHeight) {
  // cout << aWidth1 << ' ' << aHeight1 << endl;
  if ((x+offset <= xA && xA <= x+SHIP_SIZE_W-offset) && (y+offset <= yA && yA <= y+SHIP_SIZE_H-offset)){cout << "Collision" << endl;return true;}
  else if ((x+offset <= xA+aWidth && xA+aWidth <= x+SHIP_SIZE_W-offset) && (y+offset <= yA && yA <= y+SHIP_SIZE_H-offset)){cout << "Collision" << endl;return true;}
  else if ((x+offset <= xA+aWidth && xA+aWidth <= x+SHIP_SIZE_W-offset) && (y+offset <= yA+aHeight && yA+aHeight <= y+SHIP_SIZE_H-offset)){cout << "Collision" << endl;return true;}
  else if ((x+offset <= xA && xA <= x+SHIP_SIZE_W-offset) && (y+offset <= yA+aHeight && yA+aHeight <= y+SHIP_SIZE_H-offset)){cout << "Collision" << endl;return true;}
  else if ((xA <= x+SHIP_SIZE_W/2 && x+SHIP_SIZE_W/2 <= xA+aWidth) && (yA <= y+SHIP_SIZE_H/2 && y+SHIP_SIZE_H/2 <= yA+aHeight)){cout << "Collision" << endl;return true;}
  else return false;
}

bool Game::buffCollision(double x, double y, double xBuff, double yBuff) {
  if ((x+error <= xBuff && xBuff <= x+SHIP_SIZE_W-error) && (y+error <= yBuff && yBuff <= y+SHIP_SIZE_H-50)) return true;
  else if ((x+error <= xBuff+reWidth && xBuff+reWidth <= x+SHIP_SIZE_W-error) && (y+error <= yBuff && yBuff <= y+SHIP_SIZE_H-50)) return true;
  else if ((x+error <= xBuff+reWidth && xBuff+reWidth <= x+SHIP_SIZE_W-error) && (y+error <= yBuff+reHeight && yBuff+reHeight <= y+SHIP_SIZE_H-50)) return true;
  else if ((x+error <= xBuff && xBuff <= x+SHIP_SIZE_W-error) && (y+error <= yBuff+reHeight && yBuff+reHeight <= y+SHIP_SIZE_H-50)) return true;
  else return false;
}

bool Game::shootingCollision(double xFire, double yFire, double fireWidth, double fireHeight, double xA, double yA, double aWidth, double aHeight) {
  xFire = xFire + fireWidth/2, yFire = yFire+fireHeight/2;
  if ((xA <= xFire && xFire <= xA+aWidth) && (yA <= yFire && yFire <= yA+aHeight)) return true;
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

// ================================================================

void Game::resetAsteroid1(double &xA_1, double &yA_1, int &aScale1, double &step1) {
    yA_1 = -SHIP_SIZE_H;
    aScale1 = randomNumber(2,5);
    step1 = randomNumber(1,5);
    xA_1 = randomNumber(0, WIDTH);
    cout << "1: " << step1 << endl;
   if(xA_1 <= WIDTH/2) checkPos1 = true; else checkPos1 = false;
}

void Game::resetAsteroid2(double &xA_2, double &yA_2, int &aScale2, double &step2) {
    yA_2 = -SHIP_SIZE_H-100;
    aScale2 = randomNumber(2,5);
    step2 = randomNumber(1,5);
    xA_2 = randomNumber(0, WIDTH);
    cout << "2: " << step2 << endl;
   if(xA_2 <= WIDTH/2) checkPos2 = true; else checkPos2 = false;
}

// ======================================================================
void Game::wormHoleTeleportShip(Object &ship, double &x, double &y, int &width, int &height, double xWormHole, double yWormHole) {
    if((x <= xWormHole+WORM_HOLE_SIZE/2 && xWormHole+WORM_HOLE_SIZE/2 <= x+width) && (y <= yWormHole+WORM_HOLE_SIZE/2 && yWormHole+WORM_HOLE_SIZE/2 <= y+height)) {
        int i = 17, widthALt = width, heightAlt = height;
        // while (width != 1 || height != 1) {
          width = widthALt/i, height = heightAlt/i;
    x = randomNumber(SHIP_SIZE_W, WIDTH-SHIP_SIZE_W);
    y = randomNumber(SHIP_SIZE_H, HEIGHT-SHIP_SIZE_H);
          // ship.setDest(x, y, widthALt, heightAlt);
          cout << "In" << endl;
          i+=10;
        // }
    }
}