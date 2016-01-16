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
  agent_patrol.set_velocity(1.0f);
  agent_patrol.set_x(500.0f);
  agent_patrol.set_y(100.0f);

  // Patrol path points
  std::vector<Vector2D>patrol_points;
  Vector2D patrol_point1(agent_patrol.x(), agent_patrol.y());
  patrol_points.push_back(patrol_point1);
  Vector2D patrol_point2(883.0f, 93.0f);
  patrol_points.push_back(patrol_point2);
  Vector2D patrol_point3(860.0f, 574.0f);
  patrol_points.push_back(patrol_point3);
  Vector2D patrol_point4(487.0f, 579.0f);
  // Add points to vector
  patrol_points.push_back(patrol_point4);

  agent_patrol.set_patrol_points(patrol_points);

  agents.push_back(agent_patrol);



  Agent agent_mouse_follower;
  agent_mouse_follower.loadSpriteFromFile("agents/axis_medic.bmp");
  agent_mouse_follower.set_type(AGENT_TYPE::TYPE_CHASER);
  agent_mouse_follower.set_velocity(1.0f);
  agent_mouse_follower.set_x(100.0f);
  agent_mouse_follower.set_y(100.0f);


  Agent agent_random_movement;
  agent_random_movement.loadSpriteFromFile("agents/allied_engineer.bmp");
  agent_random_movement.set_type(AGENT_TYPE::TYPE_RANDOM_MOVEMENT);
  agent_random_movement.set_velocity(1.0f);
  agent_random_movement.set_x(500.0f);
  agent_random_movement.set_y(350.0f);
  agent_random_movement.set_random_radius(200.0f);
  agents.push_back(agent_random_movement);


  Agent agent_complex_commandos;
  agent_complex_commandos.loadSpriteFromFile("agents/bitmap_mask.bmp");
  agent_complex_commandos.set_type(AGENT_TYPE::TYPE_AGENT_COMMANDOS);
  agent_complex_commandos.set_velocity(1.0f);
  agent_complex_commandos.set_x(650.0f);
  agent_complex_commandos.set_y(505.0f);
  agent_complex_commandos.commandos_agent_lookout(&agents);
  agents.push_back(agent_complex_commandos);

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



    // DEBUG
    if (ESAT::IsKeyDown('P')){
      printf("MOUSE POSITION: X->%f | Y->%f\n", ESAT::MousePositionX(), ESAT::MousePositionY());
    }

    ESAT::DrawEnd();

    ESAT::WindowFrame();
  }

  ESAT::WindowDestroy();
  return 0;
}