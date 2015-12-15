

class PhysicObject{
public:
  PhysicObject();
  ~PhysicObject();

  void init();

  float x();
  float y();
  void setPosition(float x, float y);

  virtual void render();
  virtual void update();

private:
  float pos_x_;
  float pos_y_;

  float mass_;
  float speed_;
  float accel_;
};