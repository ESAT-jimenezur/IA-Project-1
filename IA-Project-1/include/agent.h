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
  void set_random_destination_point(Vector2D point);
  void set_random_radius(unsigned int radius);

  void patrol(float dt);
  void chase(float dt);
  void random_movement(float dt);

  void update(float dt);

  void commandos_agent_update(float dt);
  void commandos_agent_attitude_idle(float dt);
  void commandos_agent_lookout(std::vector<Agent> *agents_to_watch);

protected:
  AGENT_TYPE type_;
  
  // PATROL
  std::vector<Vector2D> patrol_points_;
  Vector2D current_patrol_point_;
  unsigned int current_patrol_point_index_;

  // CHASE
  Vector2D chase_objective_;
  
  // RANDOM
  unsigned int random_movement_zone_radius_;
  Vector2D random_destination_point_;

  // COMMANDOS AGENT
  // THIS IS A COMPLEX AGENT. IT CAN HAVE AN ATTITUDE.
  AGENT_TYPE commandos_agent_attitude_;
  bool commandos_think_message_shown_;
  std::vector<Agent> *agents_to_watch_;
};

#endif // !__AGENT__