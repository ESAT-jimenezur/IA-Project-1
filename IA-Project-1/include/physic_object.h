#ifndef __PHYSIC_OBJECT__
#define __PHYSIC_OBJECT__

#include <nglvector.h>

#include <drawable.h>

class PhysicObject : public Drawable{
public:
  PhysicObject();
  virtual ~PhysicObject();

  void init();
  void set_velocity(float x, float y);
  void set_acceleration(float x, float y);

  void move(float dt);

  virtual void update(float dt);

protected:
  float  dt_;
  Vector2D velocity_;
  Vector2D acceleration_;
};

#endif // !__PHYSIC_OBJECT__