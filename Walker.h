#pragma once
#include "Vector2D.h"
#include "InputHandler.h"
#include "usr/include/SDL2/SDL.h"
#include "usr/include/SDL2/SDL2_gfxPrimitives.h"

class Walker 
{
  int _x, _y;
public:
  Walker(int x, int y);
  void draw(SDL_Renderer* renderer);
  void update();
  void InputHandler();
  SDL_Texture* mTexture;   

  SDL_Rect _srcRect;
  SDL_Rect _destRect;

	Vector2D* _mousePos;
  Vector2D* _MyAngle;

	Vector2D* velocity;
	Vector2D* acceleration;
  Vector2D* location;
  
  float _angle;
};