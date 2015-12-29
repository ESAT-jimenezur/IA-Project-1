#include <stdio.h>
#include <ESAT/window.h>
#include <ESAT/time.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h>


int ESAT::main(int argc, char** argv){
  ESAT::WindowInit(1000, 700);

  // Load map
  ESAT::SpriteHandle map_sprite_handle = ESAT::SpriteFromFile("assets/maps/800x600_zel.jpg");


  float currentTime = ESAT::Time();
  float mITimeStep = 40.0;
  
  while (ESAT::WindowIsOpened()){
    int accumTime = ESAT::Time() - currentTime;
    while (accumTime >= mITimeStep) {
      currentTime += mITimeStep;
      accumTime = ESAT::Time() - currentTime;
    }
    ESAT::DrawClear(0, 0, 0, 255);
    ESAT::DrawBegin();
    // Draw

    ESAT::DrawSprite(map_sprite_handle, 0, 0);

    ESAT::DrawEnd();

    ESAT::WindowFrame();
  }

  ESAT::WindowDestroy();
  return 0;
}