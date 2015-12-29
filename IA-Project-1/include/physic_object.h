

class PhysicObject{
public:
  PhysicObject();
  ~PhysicObject();

  void init();

  float x()const;
  float y()const;
  void set_x(float x);
  void set_y(float y);
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