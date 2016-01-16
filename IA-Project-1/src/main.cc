#include <stdio.h>
#include <vector>

#include <nglvector.h>

#include <ESAT/window.h>
#include <ESAT/time.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h>

#include <agent.h>

int ESAT::main(int argc, char** argv){
  ESAT::WindowInit(1000, 700);

  std::vector<Agent> agents;

  // Load map
  ESAT::SpriteHandle map_sprite_handle = ESAT::SpriteFromFile("maps/800x600_zel.jpg");

  Agent agent_patrol;
  agent_patrol.loadSpriteFromFile("agents/allied_soldier.bmp");
  agent_patrol.set_type(AGENT_TYPE::TYPE_PATH_PATROL);
  agent_patrol.set_velocity(5.0f);
  agent_patrol.set_x(100.0f);
  agent_patrol.set_y(100.0f);

  // Patrol path points
  std::vector<Vector2D>patrol_points;
  Vector2D patrol_point1(agent_patrol.x(), agent_patrol.y());
  patrol_points.push_back(patrol_point1);
  Vector2D patrol_point2(200.0f, 100.0f);
  patrol_points.push_back(patrol_point2);
  Vector2D patrol_point3(200.0f, 200.0f);
  patrol_points.push_back(patrol_point3);
  Vector2D patrol_point4(0.0f, 200.0f);
  // Add points to vector
  patrol_points.push_back(patrol_point4);

  agent_patrol.set_patrol_points(patrol_points);

  agents.push_back(agent_patrol);



  Agent agent_mouse_follower;
  agent_mouse_follower.loadSpriteFromFile("agents/axis_medic.bmp");
  agent_mouse_follower.set_type(AGENT_TYPE::TYPE_CHASER);
  agent_mouse_follower.set_velocity(5.0f);
  agent_mouse_follower.set_x(100.0f);
  agent_mouse_follower.set_y(100.0f);


  float currentTime = ESAT::Time();
  float mITimeStep = 40.0;
  
  while (ESAT::WindowIsOpened()){

    int accumTime = ESAT::Time() - currentTime;

    float delta_time = (float)(accumTime - accumTime) / 1000;
    
    // INPUT
    
    // UPDATE
    for (unsigned int i = 0; i < agents.size(); ++i){
      agents[i].update(delta_time);
    }
    //test_object.move_to(400.0f, 100.0f, accumTime);

    while (accumTime >= mITimeStep) {
      currentTime += mITimeStep;
      accumTime = ESAT::Time() - currentTime;
    }

    agent_mouse_follower.set_chase_objective(Vector2D(ESAT::MousePositionX(), ESAT::MousePositionY()));
    agent_mouse_follower.update(delta_time);


    ESAT::DrawClear(0, 0, 0, 255);
    ESAT::DrawBegin();
    // Draw
    // First draw the map, and then, the rest above
    ESAT::DrawSprite(map_sprite_handle, 0, 0);

    for (unsigned int i = 0; i < agents.size(); ++i){
      agents[i].draw();
    }

    agent_mouse_follower.draw();

    ESAT::DrawEnd();

    ESAT::WindowFrame();
  }

  ESAT::WindowDestroy();
  return 0;
}