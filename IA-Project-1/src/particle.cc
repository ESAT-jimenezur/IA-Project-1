#include <particle.h>

Particle::Particle(){

}

Particle::~Particle(){

}

float Particle::x()const{
  return position_.x;
}

float Particle::y()const{
  return position_.y;
}

void Particle::set_x(float x){
  position_.x = x;
  initial_position_cache_.x = x;
}

void Particle::set_y(float y){
  position_.y = y;
  initial_position_cache_.y = y;
}

void Particle::setPosition(float x, float y){
  position_.x = x;
  position_.y = y;
  initial_position_cache_.x = x;
  initial_position_cache_.y = y;
}

Vector2D Particle::getInitialPosition(){
  return initial_position_cache_;
}