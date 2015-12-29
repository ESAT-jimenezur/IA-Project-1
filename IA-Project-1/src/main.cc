#include <stdio.h>
#include <vector>

#include <ESAT/window.h>
#include <ESAT/time.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h>


#include <physic_object.h>

int ESAT::main(int argc, char** argv){
  ESAT::WindowInit(1000, 700);

  std::vector<PhysicObject> agents;

  // Load map
  ESAT::SpriteHandle map_sprite_handle = ESAT::SpriteFromFile("assets/maps/800x600_zel.jpg");

  PhysicObject test_object;
  test_object.loadSpriteFromFile("assets/agents/allied_soldier.bmp");
  test_object.set_x(100.0f);
  test_object.set_y(100.0f);
  agents.push_back(test_object);


  float currentTime = ESAT::Time();
  float mITimeStep = 40.0;
  
  while (ESAT::WindowIsOpened()){
    int accumTime = ESAT::Time() - currentTime;
    
    // INPUT
    
    // UPDATE
    for (unsigned int i = 0; i < agents.size(); ++i){
      agents[i].update();
    }

    while (accumTime >= mITimeStep) {
      currentTime += mITimeStep;
      accumTime = ESAT::Time() - currentTime;
    }



    ESAT::DrawClear(0, 0, 0, 255);
    ESAT::DrawBegin();
    // Draw
    // First draw the map, and then, the rest above
    ESAT::DrawSprite(map_sprite_handle, 0, 0);

    for (unsigned int i = 0; i < agents.size(); ++i){
      agents[i].draw();
    }

    ESAT::DrawEnd();

    ESAT::WindowFrame();
  }

  ESAT::WindowDestroy();
  return 0;
}