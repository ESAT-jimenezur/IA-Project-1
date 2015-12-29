#ifndef __PHYSIC_OBJECT__
#define __PHYSIC_OBJECT__

#include <drawable.h>

class PhysicObject : public Drawable{
public:
  PhysicObject();
  virtual ~PhysicObject();

  void init();

  virtual void update();

protected:
  float mass_;
  float speed_;
  float accel_;
};

#endif // !__PHYSIC_OBJECT__