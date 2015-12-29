#ifndef __PARTICLE__
#define __PARTICLE__


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
  float pos_x_;
  float pos_y_;
};

#endif // !__PARTICLE__