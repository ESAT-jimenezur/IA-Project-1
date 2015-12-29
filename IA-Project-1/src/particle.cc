#include <particle.h>

Particle::Particle(){

}

Particle::~Particle(){

}

float Particle::x()const{
  return pos_x_;
}

float Particle::y()const{
  return pos_y_;
}

void Particle::set_x(float x){
  pos_x_ = x;
}

void Particle::set_y(float y){
  pos_y_ = y;
}

void Particle::setPosition(float x, float y){
  pos_x_ = x;
  pos_y_ = y;
}