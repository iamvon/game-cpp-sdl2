#include "game.h"

#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

int randomNumber(int minNum, int maxNum) {
  srand(time(NULL));
  return rand()%(maxNum - minNum + 1) + minNum;
}

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren);
  SDL_SetWindowTitle(win, "My game");

  TTF_Init();
  running=true; error = -20; 
  count=0; kmCounter = 0, hp = 5, healthAmount = 5;
  x = WIDTH/2 - SHIP_SIZE_W/2; y = HEIGHT - SHIP_SIZE_H - 70;
  xBg_1 = 0, yBg_1 = 0, xBg_2 = 0, yBg_2 = -HEIGHT;
  xA_1 = randomNumber(0, WIDTH - ASTEROID_SIZE/2), yA_1 = -SHIP_SIZE_H;
  angle = 0, aScale = randomNumber(1,3);
  font = TTF_OpenFont("assets/Digital_tech.otf", FONT_SIZE);

  // gem.setImage("assets/gem-3.png",ren);
  // gem.setDest(100, 100, 84, 90);
  // gem_1 = gem.createCycle(1, 84, 90, 6, 30);
  // gem.setCurAnimation(gem_1);

  ship.setSource(0, 0, IMG_SIZE_W, IMG_SIZE_H);
  ship.setImage("assets/ship-3.png", ren);
  
  for (int i = 0; i < healthAmount; ++i) {
  health[i].setSource(0, 0, 1200, 1200);
  health[i].setImage("assets/heart.png", ren);
  }
  
  asteroid1.setSource(0, 0, 320, 240);
  asteroid1.setImage("assets/asteroid-1.png", ren);

  bg1.setSource(0, 0, 1080, 1280);
  bg1.setImage("assets/bg-10.jpg", ren);

  bg2.setSource(0, 0, 1080, 1920);
  bg2.setImage("assets/bg-10.jpg", ren);
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
      kmCounter += 1;
    }
// scrolling background
  if (yBg_1 >= HEIGHT) {
     yBg_1 = 0;
     yBg_2 = -HEIGHT;
  }
// repeat random asteroid1
  if (yA_1 >= HEIGHT || conllison(x, y, xA_1, yA_1))  {
    xA_1 = randomNumber(0, WIDTH);
    yA_1 = -SHIP_SIZE_H;
    aScale = randomNumber(1,3);
  }

   if(conllison(x, y, xA_1, yA_1)) {
      cout << "conllison" << endl; 
      //  cout << countConllison << endl;
   } else cout << "not conllison" << endl;

   cout << x << " | " << xA_1 << endl;
   cout << y << " | " << yA_1 << endl;

   bg1.setDest(xBg_1, yBg_1, WIDTH, HEIGHT); yBg_1++;
   bg2.setDest(xBg_2, yBg_2, WIDTH, HEIGHT); yBg_2++;
   
   aWidth = ASTEROID_SIZE/aScale; aHeight = ASTEROID_SIZE/aScale;
   asteroid1.setDest(xA_1, yA_1, aWidth, aHeight); yA_1 += 2; angle++;
   ship.setDest(x, y, SHIP_SIZE_W, SHIP_SIZE_H);

   // update ship's health
   for (int i = 0; i < healthAmount; ++i) {
    if(conllison(x, y, xA_1, yA_1)) { --healthAmount; break;}
    // cout << healthAmount << endl;
    health[i].setDest(WIDTH - 35 - i*35, HEIGHT - 35, HEALTH_SIZE, HEALTH_SIZE);
  }

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
  // draw(gem);
  drawSpin(asteroid1, angle);

  stringstream ss;
  ss << kmCounter;
  string ssKm = ss.str();
  const char* km = ssKm.c_str();

  drawMsg(km, 80, 80, 234, 123, 123);
  drawMsg("KM", 140, 80, 234, 123, 123);

   // update ship's health
  for(int i = 0; i < healthAmount; ++i) {
   draw(health[i]);
  }
  draw(ship);

  frameCount++;
  int timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(BACKGROUND_SPEED/FPS)) {
    SDL_Delay((BACKGROUND_SPEED/FPS)-timerFPS);
  }

  SDL_RenderPresent(ren);
}

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

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}
    if(e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
      
      // di chuyển và bo viền 
      if(0 >= x) x = 0; if(x > WIDTH-SHIP_SIZE_W) x = WIDTH-SHIP_SIZE_W;
      if(e.key.keysym.sym == SDLK_LEFT && (0 <= x && x <= WIDTH-SHIP_SIZE_W)) x -= SHIP_SPEED_MOVE;
      if(e.key.keysym.sym == SDLK_RIGHT && (0 <= x && x <= WIDTH-SHIP_SIZE_W)) x += SHIP_SPEED_MOVE;
    }
    if(e.type == SDL_KEYUP) {
    }
     SDL_GetMouseState(&mouseX, &mouseY);
  }
}

void Game::update() {
  // gem.updateAnimation();
}

bool Game::conllison(int x, int y, int &xA_1, int &yA_1) {
  // cout << aWidth << ' ' << aHeight << endl;
  if ((x <= xA_1 && xA_1 <= x+SHIP_SIZE_W) && (y <= yA_1+error)) return true;
  else if ((x <= xA_1+aWidth && xA_1+aWidth <= x+SHIP_SIZE_W) && (y <= yA_1+error)) return true;
  else if ((x <= xA_1+aWidth && xA_1+aWidth <= x+SHIP_SIZE_W) && (y <= yA_1+aHeight+error)) return true;
  else if ((x <= xA_1 && xA_1 <= x+SHIP_SIZE_W) && (y <= yA_1+aHeight+error)) return true;
  else return false;
}
