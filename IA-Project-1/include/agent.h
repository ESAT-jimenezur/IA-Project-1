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

  void change_agent_type(AGENT_TYPE new_type);

  void set_patrol_points(std::vector<Vector2D> points);
  void set_chase_objective(Vector2D objective);
  void set_follow_objective(Agent *objective);
  void set_random_destination_point(Vector2D point);
  void set_random_radius(unsigned int radius);

  void patrol(float dt);
  void chase(float dt);
  void follow(float dt);
  void random_movement(float dt);

  void update(float dt);

  void commandos_agent_update(float dt);
  void commandos_agent_attitude_idle(float dt);
  void commandos_agent_attitude_chaser(float dt);
  void commandos_agent_attitude_take_to_jail(float dt);
  void commandos_return_to_position(float dt);
  void commandos_agent_lookout(std::vector<Agent> *agents_to_watch);

protected:
  AGENT_TYPE type_;
  bool can_be_chased_;
  
  // PATROL
  std::vector<Vector2D> patrol_points_;
  Vector2D current_patrol_point_;
  unsigned int current_patrol_point_index_;

  // CHASE
  Vector2D chase_objective_;
  Agent *follow_objective_agent_;
  
  // RANDOM
  unsigned int random_movement_zone_radius_;
  Vector2D random_destination_point_;

  // COMMANDOS AGENT
  // THIS IS A COMPLEX AGENT. IT CAN HAVE AN ATTITUDE.
  AGENT_TYPE commandos_agent_attitude_;
  float commandos_agent_idling_time_;
  bool commandos_think_message_shown_;
  bool commandos_is_chasing_objective_;
  bool commandos_is_taking_objective_to_jail_;
  bool commandos_finished_mission_;
  bool commandos_should_return_to_position_;
  std::vector<Agent> *agents_to_watch_;
  Agent *agent_to_chase_;
};

#endif // !__AGENT__