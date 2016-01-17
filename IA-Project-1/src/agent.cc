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
  can_be_chased_ = true;
  commandos_agent_attitude_ = AGENT_TYPE::TYPE_IDLE;
  commandos_think_message_shown_ = false;
  current_patrol_point_index_ = 0;
  random_movement_zone_radius_ = 50;
  commandos_agent_idling_time_ = 0.0f;
  commandos_is_chasing_objective_ = false;
  commandos_is_taking_objective_to_jail_ = false;
  commandos_finished_mission_ = false;
  commandos_should_return_to_position_ = false;
  agents_to_watch_ = NULL;
}

Agent::~Agent(){

}

void Agent::set_type(AGENT_TYPE type){
  type_ = type;
}

void Agent::change_agent_type(AGENT_TYPE new_type){
  type_ = new_type;
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
  case AGENT_TYPE::TYPE_FOLLOWING:
    follow(dt);
    break;
  case AGENT_TYPE::TYPE_RANDOM_MOVEMENT:
    random_movement(dt);
    break;
  case AGENT_TYPE::TYPE_AGENT_COMMANDOS:
    commandos_agent_update(dt);
    break;
  default:
    break;
  }

}

void Agent::commandos_agent_update(float dt){
  // BRAIN

  if (commandos_should_return_to_position_){
    commandos_return_to_position(dt); 
  }else{
    switch (commandos_agent_attitude_){
    case AGENT_TYPE::TYPE_IDLE:
      commandos_agent_attitude_idle(dt);
      break;
    case AGENT_TYPE::TYPE_CHASER:
      commandos_agent_attitude_chaser(dt);
      break;
    case AGENT_TYPE::TYPE_WALKER:
      commandos_agent_attitude_take_to_jail(dt);
      break;
    default:
      break;
    }
  }

}

void Agent::commandos_agent_lookout(std::vector<Agent> *agents_to_watch){
  agents_to_watch_ = agents_to_watch;
}

void Agent::commandos_agent_attitude_idle(float dt){

  if (!commandos_think_message_shown_){
    printf("COMMANDOS AGENT: I'll stay here, I need to protect this house against the vandals\n");
    commandos_think_message_shown_ = true;
  }

  if (agents_to_watch_ != NULL && agents_to_watch_ > 0){

    for (unsigned int i = 0; i < agents_to_watch_->size(); ++i){
      if (agents_to_watch_->at(i).type_ != AGENT_TYPE::TYPE_AGENT_COMMANDOS &&
          agents_to_watch_->at(i).can_be_chased_){
        
        // If that agent (who we are watching) is near enough, follow him
        if (is_near_enought(position_, agents_to_watch_->at(i).position_, 100.0f)){
          commandos_agent_attitude_ = AGENT_TYPE::TYPE_CHASER;
          agent_to_chase_ = &agents_to_watch_->at(i);
          commandos_think_message_shown_ = false;
          commandos_is_chasing_objective_ = true;
        }
      }
    }
  
  }
}

void Agent::commandos_agent_attitude_chaser(float dt){
  
  if (!commandos_think_message_shown_){
    printf("COMMANDOS AGENT: Hey man, what are you doing! STOP!!!\n");
    commandos_think_message_shown_ = true;
  }

  if (agent_to_chase_ != NULL){
    if (commandos_is_chasing_objective_){
      move_to(agent_to_chase_->position_.x, agent_to_chase_->position_.y, dt);
    }

    // TODO
    //printf("PUNCH!\n");
    if (is_near_enought(position_, agent_to_chase_->position_, 10.0f) &&
        commandos_is_chasing_objective_){
      agent_to_chase_->change_agent_type(AGENT_TYPE::TYPE_FOLLOWING);
      agent_to_chase_->set_follow_objective(this);
      commandos_agent_attitude_ = AGENT_TYPE::TYPE_WALKER;
      commandos_is_chasing_objective_ = false;
      commandos_is_taking_objective_to_jail_ = true;
      commandos_think_message_shown_ = false;
    }

  }

}

void Agent::commandos_agent_attitude_take_to_jail(float dt){
  
  // Take objective to jail
  if (agent_to_chase_ != NULL){
    // TAKE THE PRISONER TO JAIL
    // X 696.0 - Y 420.0
    move_to(696.0f, 420.0f, dt);
  }

  if (is_near_enought(position_, Vector2D(696.0f, 420.0f), 10) &&
    commandos_is_taking_objective_to_jail_){
    if (!commandos_think_message_shown_){
      printf("COMMANDOS AGENT: You are now my prisoner.!\n");
      commandos_think_message_shown_ = true;
    }
    agent_to_chase_->change_agent_type(AGENT_TYPE::TYPE_IDLE);
    commandos_is_taking_objective_to_jail_ = false;
    agent_to_chase_->can_be_chased_ = false;
    commandos_finished_mission_ = true;
    commandos_should_return_to_position_ = true;
    commandos_think_message_shown_ = false;
  }
}

void Agent::commandos_return_to_position(float dt){
  if (!commandos_think_message_shown_){
    printf("COMMANDOS AGENT: I will return to my position!\n");
    commandos_think_message_shown_ = true;
  }
  move_to(initial_position_cache_.x, initial_position_cache_.y, dt);
  if (is_near_enought(position_, initial_position_cache_, 10)){
    commandos_agent_attitude_ = AGENT_TYPE::TYPE_IDLE;
    commandos_should_return_to_position_ = false;
    commandos_finished_mission_ = false;
    commandos_think_message_shown_ = false;
    commandos_agent_idling_time_ = 0.0f;
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

void Agent::set_follow_objective(Agent *objective){
  follow_objective_agent_ = objective;
}

void Agent::set_random_destination_point(Vector2D point){
  random_destination_point_ = point;
}

void Agent::set_random_radius(unsigned int radius){
  random_movement_zone_radius_ = radius;
  random_destination_point_.x = rand() % (unsigned int)initial_position_cache_.x + (random_movement_zone_radius_);
  random_destination_point_.y = rand() % (unsigned int)initial_position_cache_.y + (random_movement_zone_radius_);
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

void Agent::follow(float dt){
  move_to(follow_objective_agent_->position_.x, follow_objective_agent_->position_.y, dt);
}

void Agent::random_movement(float dt){
  if (is_near_enought(position_, random_destination_point_, 5.0f) ||
    position_.x < 0.0f || position_.x > 1000.0f ||
    position_.y < 0.0f || position_.y > 700
    ){ // Also calculate new point if the agent is going to go outside the map
    // Agent arrived to destination, calculate new random point
    random_destination_point_.x = rand() % (unsigned int)initial_position_cache_.x + (random_movement_zone_radius_);
    random_destination_point_.y = rand() % (unsigned int)initial_position_cache_.y + (random_movement_zone_radius_);
  }else{
    move_to(random_destination_point_.x, random_destination_point_.y, dt);
  }
}