#include <agent.h>


Agent::Agent(){
  type_ = AGENT_TYPE::TYPE_STILL;
}

Agent::~Agent(){

}

void Agent::update(float dt){
  PhysicObject::update(dt);
  
}