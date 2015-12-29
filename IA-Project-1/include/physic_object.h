#ifndef __PHYSIC_OBJECT__
#define __PHYSIC_OBJECT__

#include <drawable.h>

class PhysicObject : public Drawable{
public:
  PhysicObject();
  ~PhysicObject();

  void init();

  virtual void update();

private:


  float mass_;
  float speed_;
  float accel_;
};

#endif // !__PHYSIC_OBJECT__