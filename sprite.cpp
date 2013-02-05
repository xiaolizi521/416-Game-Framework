#include <iostream>
#include <cmath>
#include <limits>
#include "sprite.h"
#include "gamedata.h"

Sprite::Sprite(const std::string& name, const Frame* fm) :
  Drawable(name,
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"),
                    Gamedata::getInstance()->getXmlInt(name+"Y")),
           Vector2f(
             (rand()%2?1:-1)*Random::getInstance().getRand(
                Gamedata::getInstance()->getXmlInt(name+"SpeedXMin"),
                Gamedata::getInstance()->getXmlInt(name+"SpeedXMax")),
             (rand()%2?1:-1)*Random::getInstance().getRand(
                  Gamedata::getInstance()->getXmlInt(name+"SpeedYMin"),
                  Gamedata::getInstance()->getXmlInt(name+"SpeedYMax")))
  ),
  acceleration(
      Gamedata::getInstance()->getXmlInt(name+"AccelX"),
      Gamedata::getInstance()->getXmlInt(name+"AccelY")
  ),
  maxSpeeds(
      Gamedata::getInstance()->getXmlInt(name+"SpeedXMax"),
      Gamedata::getInstance()->getXmlInt(name+"SpeedYMax")
  ),
  spriteName(name),
  frame(fm)
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()),
  acceleration(s.acceleration),
  maxSpeeds(s.maxSpeeds),
  spriteName(s.spriteName),
  frame(s.frame)
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  frame = rhs.frame;
  return *this;
}

void Sprite::draw() const {
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y);
}

unsigned Sprite::getPixel(Uint32 i, Uint32 j) const {
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}


int Sprite::getDistance(const Sprite *obj) const {
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::updateVelocity(Uint32 ticks){

  float inc = acceleration[0] * 0.001 * static_cast<float>(ticks);
  velocityX( velocityX() + inc );

  inc = acceleration[0] * 0.001 * static_cast<float>(ticks);
  velocityY( velocityY() + inc );

  if(velocityX() > maxSpeeds[0]) {
    velocityX( maxSpeeds[0] );
  }

  if(velocityY() > maxSpeeds[1]) {
    velocityY( maxSpeeds[1] );
  }
}


void Sprite::update(Uint32 ticks) {
  updateVelocity(ticks);

  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  float height = static_cast<float>(frame->getHeight());
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > Gamedata::getInstance()->getXmlInt("worldHeight")-height) {
    velocityY( -abs( velocityY() ) );
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(frame->getWidth());
  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("worldWidth")-width) {
    velocityX( -abs( velocityX() ) );
  }
}
