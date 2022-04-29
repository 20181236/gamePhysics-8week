#define WIDTH (600)
#define HEIGHT (400)

#include "Game.h"
#include "InputHandler.h"

#include "Walker.h"

Game* Game::s_pInstance = 0;

bool Game::setup()
{
    //git to pc 테스트
 bool result;

 result = init("Nature of Code", 0, 0, WIDTH, HEIGHT, false);

_walker = new Walker(WIDTH/2,HEIGHT/2);

 SDL_Surface* pTempSurface = IMG_Load("Assets/arrow.png");

 
 mTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), pTempSurface);
  
 SDL_FreeSurface(pTempSurface);

 _srcRect.x =_srcRect.y = 0;
  SDL_QueryTexture(mTexture, NULL, NULL, &_srcRect.w, &_srcRect.h);


 _destRect.x =WIDTH/2 ;
 _destRect.y = HEIGHT/2;

 _destRect.w = _srcRect.w;
 _destRect.h = _srcRect.h;


  location=new Vector2D(_destRect.x,_destRect.y);
  velocity=new Vector2D();
  acceleration=new Vector2D();
  
 return result;
}

void Game::update()
{
  /*P
Vector mouse = new PVector(mouseX,mouseY);
PVector dir = PVector.sub(mouse,location);
*/
 _mousePos = TheInputHandler::Instance()->getMousePosition();
_walker->update();  
  Vector2D dir(_mousePos->getX() - _srcRect.w/2,_mousePos->getY() - _srcRect.h/2);
  
/* 원문
  float anything = ?????
dir.normalize();
dir.mult(anything);*/
//PVector dir = PVector.sub(mouse,location);
  dir.Sub(location); 
  dir.normalize();
  dir.Mult(0.5f);
  /*원문
    acceleration = dir;
 
    velocity.add(acceleration);
    velocity.limit(topspeed);
    location.add(velocity);
*/
  acceleration->setX(dir.getX());
  acceleration->setY(dir.getY());

  velocity->Add(acceleration);
   
  velocity->limit(topspeed);
  
  location->Add(velocity); 

/*
_destRect.x = _mousePos->getX() - _srcRect.w/2;
_destRect.y = _mousePos->getY() - _srcRect.h/2;
위치 = 위치 + 벡터..?
*/
_destRect.x = location->getX();
_destRect.y = location->getY();

  
 _angle = atan2(_destRect.y - HEIGHT/2 , _destRect.x - WIDTH/2 ) * 180 / 3.1415926535;

 SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
}
 
void Game::render()
{
 SDL_RenderClear(m_pRenderer); 

filledCircleRGBA(m_pRenderer, _mousePos->getX(), _mousePos->getY(), 10, 255, 0, 0, 255);

_walker->draw(m_pRenderer);

 SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), mTexture, &_srcRect, &_destRect, _angle, 0, SDL_FLIP_NONE);

 SDL_RenderPresent(m_pRenderer); 
}

void Game::clean() 
{
delete _walker;
 
 TheInputHandler::Instance()->clean();
 
 SDL_DestroyWindow(m_pWindow);
 SDL_DestroyRenderer(m_pRenderer);

 m_pWindow = NULL;
 m_pRenderer = NULL;

 SDL_Quit();
}

//==================================================

bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags) 
{
 if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
 {
 return false;
 }

 m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL);
 
 if (m_pWindow != NULL ) 
 {
 m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
 
 SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255); 
 SDL_RenderClear(m_pRenderer);
 } 
 else 
 {
 return false; // 윈도우 생설 실패 l
 }
 
 m_bRunning = true;
 
 SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

 return true;
}

bool Game::running()
{ 
 return m_bRunning; 
}

void Game::handleEvents() 
{
 TheInputHandler::Instance()->update();
}