#include <physic_object.h>


PhysicObject::PhysicObject(){
  velocity_ = { 0, 0 };
  acceleration_ = { 0, 0 };
}

PhysicObject::~PhysicObject(){

}


void PhysicObject::update(float dt){
  move(dt);
}

void PhysicObject::setVelocity(float x, float y){
  velocity_.x = x;
  velocity_.y = y;
}

void PhysicObject::setAcceleration(float x, float y){
  acceleration_.x = x;
  acceleration_.y = y;
}

void PhysicObject::move(float dt){
  float time = dt * 0.001;
  velocity_ = velocity_ + (acceleration_ * time);
  position_ = position_ + (velocity_ * time + ((acceleration_ * 0.5f) * (time * time)));
}