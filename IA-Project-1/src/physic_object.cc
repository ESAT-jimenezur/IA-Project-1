#include <physic_object.h>


PhysicObject::PhysicObject(){
  velocity_ = { 0, 0 };
  acceleration_ = { 0, 0 };
}

PhysicObject::~PhysicObject(){

}


void PhysicObject::update(float dt){
  
}
void PhysicObject::set_velocity(float vel){
  velocity_.x = vel;
  velocity_.y = vel;
}
void PhysicObject::set_velocity(float x, float y){
  velocity_.x = x;
  velocity_.y = y;
}

void PhysicObject::set_acceleration(float x, float y){
  acceleration_.x = x;
  acceleration_.y = y;
}

void PhysicObject::move(float dt){
  float time = dt * 0.001;
  velocity_ = velocity_ + (acceleration_ * time);
  position_ = position_ + (velocity_ * time + ((acceleration_ * 0.5f) * (time * time)));
}


void PhysicObject::move_to(float x, float y, float dt){
  float time = dt * 0.001;
  if (position_.x < x){
    velocity_.x = (unsigned int)velocity_.x + (acceleration_.x * time);
    position_.x = position_.x + (velocity_.x * time + ((acceleration_.x * 0.5f) * (time * time)));
  }
  else{
    velocity_.x = (unsigned int)velocity_.x + (acceleration_.x * time);
    position_.x = position_.x - (velocity_.x * time + ((acceleration_.x * 0.5f) * (time * time)));
  }
}