#ifndef __AGENT__
#define __AGENT__

#include <constants.h>
#include <physic_object.h>

class Agent : public PhysicObject{
public:

  Agent();
  ~Agent();

  AGENT_TYPE type()const;
  void set_type(AGENT_TYPE type);

  void update(float dt);

private:
  AGENT_TYPE type_;
};

#endif // !__AGENT__