#include <cmath>
#include <time.h>
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
  srand(time(NULL));
  type_ = AGENT_TYPE::TYPE_IDLE;
  current_patrol_point_index_ = 0;
  random_movement_zone_radius_ = 50;
}

Agent::~Agent(){

}

void Agent::set_type(AGENT_TYPE type){
  type_ = type;
}


void Agent::update(float dt){
  PhysicObject::update(dt);

  switch (type_){
  case AGENT_TYPE::TYPE_IDLE:
    break;
  case AGENT_TYPE::TYPE_PATH_PATROL:
    patrol(dt);
    break;
  case AGENT_TYPE::TYPE_CHASER:
    chase(dt);
    break;
  case AGENT_TYPE::TYPE_RANDOM_MOVEMENT:
    random_movement(dt);
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

void Agent::set_random_destination_point(Vector2D point){
  random_destination_point_ = point;
}

void Agent::set_random_radius(unsigned int radius){
  random_movement_zone_radius_ = radius;
  random_destination_point_.x = rand() % (unsigned int)position_.x + (random_movement_zone_radius_);
  random_destination_point_.y = rand() % (unsigned int)position_.y + (random_movement_zone_radius_);
}

void Agent::patrol(float dt){
  if (is_near_enought(position_, current_patrol_point_, 5.0f)){
    // Agent arrived to destination, retrieve next patrol point
    current_patrol_point_index_++;
    if (current_patrol_point_index_ >= patrol_points_.size()){
      // If no more patrol points, go to first
      current_patrol_point_index_ = 0;
    }
    current_patrol_point_ = patrol_points_[current_patrol_point_index_];
  }else{
    move_to(current_patrol_point_.x, current_patrol_point_.y, dt);
  }
}

void Agent::chase(float dt){
  move_to(chase_objective_.x, chase_objective_.y, dt);
}

void Agent::random_movement(float dt){
  if (is_near_enought(position_, random_destination_point_, 5.0f) ||
    position_.x < 0.0f || position_.x > 1000.0f ||
    position_.y < 0.0f || position_.y > 700
    ){ // Also calculate new point if the agent is going to go outside the map
    // Agent arrived to destination, calculate new random point
    random_destination_point_.x = rand() % (unsigned int)position_.x + (random_movement_zone_radius_);
    random_destination_point_.y = rand() % (unsigned int)position_.y + (random_movement_zone_radius_);
  }else{
    move_to(random_destination_point_.x, random_destination_point_.y, dt);
  }
}