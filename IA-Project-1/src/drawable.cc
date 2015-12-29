#include <drawable.h>


Drawable::Drawable(){
  sprite_ == nullptr;
}

Drawable::~Drawable(){
  //ESAT::SpriteRelease(sprite_);
}

float Drawable::x()const{
  return pos_x_;
}

float Drawable::y()const{
  return pos_y_;
}

void Drawable::set_x(float x){
  pos_x_ = x;
}

void Drawable::set_y(float y){
  pos_y_ = y;
}

void Drawable::setPosition(float x, float y){
  pos_x_ = x;
  pos_y_ = y;
}

void Drawable::loadSpriteFromFile(const char* path){
  sprite_ = ESAT::SpriteFromFile(path);
}

void Drawable::draw(){
  ESAT::DrawSprite(sprite_, pos_x_, pos_y_);
}