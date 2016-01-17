#include <stdio.h>
#include <vector>
#include <map>

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
  bool paused = false;

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




  Agent agent_patrol2;
  agent_patrol2.loadSpriteFromFile("agents/allied_soldier.bmp");
  agent_patrol2.set_type(AGENT_TYPE::TYPE_PATH_PATROL);
  agent_patrol2.set_velocity(1.0f);
  agent_patrol2.set_x(75.0f);
  agent_patrol2.set_y(610.0f);

  // Patrol path points
  std::vector<Vector2D>patrol2_points;
  Vector2D patrol2_point(agent_patrol2.x(), agent_patrol2.y());
  patrol2_points.push_back(patrol2_point);
  Vector2D patrol2_point2(670.0f, 590.0f);
  patrol2_points.push_back(patrol2_point2);
  // Add points to vector

  agent_patrol2.set_patrol_points(patrol2_points);
  agents.push_back(agent_patrol2);


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
  agent_random_movement.set_y(400.0f);
  agent_random_movement.set_random_radius(200.0f);
  agents.push_back(agent_random_movement);
  
  Agent agent_random_movement2;
  agent_random_movement2.loadSpriteFromFile("agents/allied_engineer.bmp");
  agent_random_movement2.set_type(AGENT_TYPE::TYPE_RANDOM_MOVEMENT);
  agent_random_movement2.set_velocity(1.0f);
  agent_random_movement2.set_x(860.0f);
  agent_random_movement2.set_y(350.0f);
  agent_random_movement2.set_random_radius(200.0f);
  agents.push_back(agent_random_movement2);


  //Agent pattern
  Agent agent_patterns;
  agent_patterns.loadSpriteFromFile("agents/allied_flag.bmp");
  agent_patterns.set_type(AGENT_TYPE::TYPE_PATTERN);
  agent_patterns.set_velocity(1.0f);
  agent_patterns.set_x(475.0f);
  agent_patterns.set_y(375.0f);
  agent_patterns.add_pattern(PATTERN_UP, 3.0f);
  agent_patterns.add_pattern(PATTERN_LEFT, 3.0f);
  agent_patterns.add_pattern(PATTERN_RIGHT, 3.0f);
  agent_patterns.add_pattern(PATTERN_DOWN, 3.0f);

  agents.push_back(agent_patterns);


  Agent agent_complex_commandos;
  agent_complex_commandos.loadSpriteFromFile("agents/bitmap_mask.bmp");
  agent_complex_commandos.set_type(AGENT_TYPE::TYPE_AGENT_COMMANDOS);
  agent_complex_commandos.set_velocity(1.0f);
  agent_complex_commandos.set_x(650.0f);
  agent_complex_commandos.set_y(505.0f);
  agent_complex_commandos.commandos_agent_lookout(&agents);
  agents.push_back(agent_complex_commandos);


  float lastTime = ESAT::Time();
  float mITimeStep = 40.0;
  float delta_time = 0.0f;
  
  while (ESAT::WindowIsOpened()){

    float thisTime = ESAT::Time();

    delta_time = (float)(thisTime - lastTime) / 1000;
    
    // INPUT
    
    // UPDATE
    while (lastTime >= mITimeStep) {
      lastTime += mITimeStep;
      lastTime = ESAT::Time() - lastTime;
    }

    if (!paused){
      
      for (unsigned int i = 0; i < agents.size(); ++i){
        agents[i].update(delta_time);
      }

      agent_mouse_follower.set_chase_objective(Vector2D(ESAT::MousePositionX(), ESAT::MousePositionY()));
      agent_mouse_follower.update(delta_time);

    }

    ESAT::DrawClear(0, 0, 0, 255);
    ESAT::DrawBegin();
    // Draw
    // First draw the map, and then, the rest above
    ESAT::DrawSprite(map_sprite_handle, 0, 0);

    for (unsigned int i = 0; i < agents.size(); ++i){
      agents[i].draw();
    }

    agent_mouse_follower.draw();



    // PAUSE
    if (ESAT::IsSpecialKeyDown(kSpecialKey_Space)){
      if (paused){
        paused = false;
        printf(" *** UNPAUSED *** \n");
      }else{
        paused = true;
        printf(" *** PAUSED *** \n");
      }
      
    }
    
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