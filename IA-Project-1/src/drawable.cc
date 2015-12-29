#include <drawable.h>


Drawable::Drawable(){
  sprite_ == nullptr;
}

Drawable::~Drawable(){
  //ESAT::SpriteRelease(sprite_);
}

void Drawable::loadSpriteFromFile(const char* path){
  sprite_ = ESAT::SpriteFromFile(path);
}

void Drawable::draw(){
  ESAT::DrawSprite(sprite_, position_.x, position_.y);
}