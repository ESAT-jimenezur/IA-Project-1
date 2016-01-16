#ifndef __AGENT__
#define __AGENT__

#include <vector>

#include <nglvector.h>

#include <constants.h>
#include <physic_object.h>

class Agent : public PhysicObject{
public:

  Agent();
  ~Agent();

  AGENT_TYPE type()const;
  void set_type(AGENT_TYPE type);

  void set_patrol_points(std::vector<Vector2D> points);
  void set_chase_objective(Vector2D objective);

  void patrol(float dt);
  void chase(float dt);

  void update(float dt);

private:
  AGENT_TYPE type_;
  std::vector<Vector2D> patrol_points_;
  Vector2D current_patrol_point_;
  unsigned int current_patrol_point_index_;

  Vector2D chase_objective_;

  bool arrived_x_;
  bool arrived_y_;
};

#endif // !__AGENT__