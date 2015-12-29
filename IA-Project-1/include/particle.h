#ifndef __PARTICLE__
#define __PARTICLE__

#include <nglvector.h>

#include <ESAT/sprite.h>

class Particle{
public:
  Particle();
  virtual ~Particle();

  float x()const;
  float y()const;
  void set_x(float x);
  void set_y(float y);
  void setPosition(float x, float y);

protected:
  Vector2D position_;
};

#endif // !__PARTICLE__