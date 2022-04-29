#include "Game.h"
#include "Vector2D.h"
#include "InputHandler.h"

class Mover {
public:
  Mover() {
  Vector2D* acceleration;
  Vector2D* velocity;
  //Vector2D* pos = createVector(random(width), random(height));
  float topSpeed = 4.0f;
  void draw(SDL_Renderer* renderer);
  void update();
  void InputHandler();
  //viod display();
}
};

/*
class Mover {

  constructor() {
    this.acceleration = createVector();
    this.velocity = createVector(0, 0);
    this.pos = createVector(random(width), random(height));
    this.topSpeed = 4;
  }*/