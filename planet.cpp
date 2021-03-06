#include "planet.h"
#include "frameFactory.h"

Planet::Planet(const std::string& name, float m, float r, Vector2f pos):
  Drawable(name,pos,Vector2f(0,0)),
  frame(FrameFactory::getInstance().getFrame(name)),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  mass(m),
  radius(r)
{}

Planet::Planet(const Planet& o):
  Drawable(o.getName(),o.getPosition(),o.getVelocity()),
  frame(o.getFrame()),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  mass(o.mass),
  radius(o.radius)
{}

Planet& Planet::operator=(const Planet& other){
  if(this == &other)
    return *this;

  setName(other.getName());
  setPosition(other.getPosition());
  setVelocity(other.getVelocity());

  frame = other.frame;
  frameWidth = other.frameWidth;
  frameHeight = other.frameHeight;

  mass = other.mass;
  radius = other.radius;

  return *this;
}

Vector2f Planet::getLocation() const {
  return Vector2f(X()+radius,Y()+radius);
}

void Planet::draw() const{
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y);
}
