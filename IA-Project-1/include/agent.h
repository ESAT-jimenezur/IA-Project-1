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
  void patrol(float dt);


  void update(float dt);

  bool is_near_enought(Vector2D point, Vector2D dest_center, float radius);

private:
  AGENT_TYPE type_;
  std::vector<Vector2D> patrol_points_;
  Vector2D current_patrol_point_;
  unsigned int current_patrol_point_index_;

  bool arrived_x_;
  bool arrived_y_;
};

#endif // !__AGENT__