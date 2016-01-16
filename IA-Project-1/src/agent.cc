#include <cmath>
#include <agent.h>


/*
 Estados:
  IDLE
  Chasing
  Returning (optional)
  Running away (huye del objetivo)
  Looking

 Movimientos:
  Stand
  Determinista (Go to point)
  Tracking (Perseguir)
*/

Agent::Agent(){
  type_ = AGENT_TYPE::TYPE_STILL;
  current_patrol_point_index_ = 0;
  arrived_x_ = false;
  arrived_y_ = false;
}

Agent::~Agent(){

}

void Agent::set_type(AGENT_TYPE type){
  type_ = type;
}


void Agent::update(float dt){
  PhysicObject::update(dt);

  switch (type_){
  case AGENT_TYPE::TYPE_STILL:
    break;
  case AGENT_TYPE::TYPE_PATH_PATROL:
    patrol(dt);
    break;
  case AGENT_TYPE::TYPE_CHASER:
    chase(dt);
    break;
  default:
    break;
  }

}

void Agent::set_patrol_points(std::vector<Vector2D> points){
  patrol_points_ = points;
  current_patrol_point_index_ = 0;
  current_patrol_point_ = points[current_patrol_point_index_]; // First patrol point
}

void Agent::set_chase_objective(Vector2D objective){
  chase_objective_ = objective;
}

void Agent::patrol(float dt){
  //printf("posx: %d | %d - posy : %d | %d\n", position_.x, current_patrol_point_.x, position_.y, current_patrol_point_.y);
  
  
  //printf("%d\n", current_patrol_point_index_);

  if (is_near_enought(position_, current_patrol_point_, 5.0f)){
    current_patrol_point_index_++;
    if (current_patrol_point_index_ >= patrol_points_.size()){
      current_patrol_point_index_ = 0;
    }
    current_patrol_point_ = patrol_points_[current_patrol_point_index_];
    
    //arrived_x_ = false;
    //arrived_y_ = false;
    //printf("%d\n", current_patrol_point_);
  }else{
    move_to(current_patrol_point_.x, current_patrol_point_.y, dt);
  }

}

void Agent::chase(float dt){
  move_to(chase_objective_.x, chase_objective_.y, dt);
}