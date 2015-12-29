#ifndef __DRAWABLE__
#define __DRAWABLE__


#include <ESAT/sprite.h>

#include <particle.h>

class Drawable : public Particle{
public:
  Drawable();
  virtual ~Drawable();

  virtual void draw();
  void loadSpriteFromFile(const char* path);

protected:
  ESAT::SpriteHandle sprite_;
};

#endif // !__DRAWABLE__