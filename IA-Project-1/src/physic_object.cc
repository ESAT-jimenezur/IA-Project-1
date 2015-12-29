#include <physic_object.h>


PhysicObject::PhysicObject(){
  pos_x_ = 0.0f;
  pos_y_ = 0.0f;
  
  mass_ = 0;
  speed_ = 0;
  accel_ = 0;
}

PhysicObject::~PhysicObject(){

}

float PhysicObject::x()const{
  return pos_x_;
}

float PhysicObject::y()const{
  return pos_y_;
}

void PhysicObject::set_x(float x){
  pos_x_ = x;
}

void PhysicObject::set_y(float y){
  pos_y_ = y;
}

void PhysicObject::setPosition(float x, float y){
  pos_x_ = x;
  pos_y_ = y;
}


void PhysicObject::render(){

}


void PhysicObject::update(){

}