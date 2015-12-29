#ifndef __DRAWABLE__
#define __DRAWABLE__


#include <ESAT/sprite.h>

class Drawable{
public:
  Drawable();
  ~Drawable();

  float x()const;
  float y()const;
  void set_x(float x);
  void set_y(float y);
  void setPosition(float x, float y);
  virtual void draw();
  void loadSpriteFromFile(const char* path);

private:
  ESAT::SpriteHandle sprite_;

  float pos_x_;
  float pos_y_;

};

#endif // !__DRAWABLE__