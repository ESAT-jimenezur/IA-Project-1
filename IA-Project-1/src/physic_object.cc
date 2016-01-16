#define _USE_MATH_DEFINES
#include <cmath>

#include "physic_object.h"


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
  float time = dt;

  float delta_x = x - position_.x; /*difference in x positions*/
  float delta_y = y - position_.y; /*difference in y positions*/

  /*Move the target toward */
  double tangent = (delta_y / delta_x); //find angle
  double angle = atan(tangent) * (180 / M_PI); //important for direction
  
  //double dx = cos(angle) * velocity_.x;
  //double dy = sin(angle) * velocity_.y;

  float length = sqrt(delta_x*delta_x + delta_y*delta_y);

  delta_x /= length;
  delta_y /= length;

  float speed_x = velocity_.x + (acceleration_.x * time);
  float speed_y = velocity_.y + (acceleration_.y * time);

  delta_x *= speed_x;
  delta_y *= speed_y;

  /*Move the target toward the cursor/user*/
  position_.x = position_.x + delta_x; //original x position changed by dx
  position_.y = position_.y + delta_y; //original y position changed by dy
}

bool PhysicObject::is_near_enought(Vector2D point, Vector2D dest_center, float radius){
  float dist = sqrt( pow( (point.x - dest_center.x), 2) + pow( (point.y - dest_center.y), 2) );
  //printf("%f - %f\n", dist, pow(radius, 2));
  return dist <= radius;
}