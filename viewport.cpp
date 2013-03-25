
#include "ioManager.h"
#include "viewport.h"
#include "clock.h"
#include "hud.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() :
  jgdata(JSONGamedata::getInstance()),
  position(0, 0),
  viewWidth(jgdata.getInt("view.width")),
  viewHeight(jgdata.getInt("view.height")),
  worldWidth(jgdata.getInt("world.width")),
  worldHeight(jgdata.getInt("world.height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL)
{}

void Viewport::setObjectToTrack(const Drawable *obj) {
  objectToTrack = obj;
  objWidth = objectToTrack->getFrame()->getWidth();
  objHeight = objectToTrack->getFrame()->getHeight();
}

void Viewport::draw() const {
  IOManager::getInstance().
    printMessageCenteredAt("Tracking "+objectToTrack->getName(),
        jgdata.getInt("trackText.y"));
}

void Viewport::drawHUD() const {
  HUD::getHUD().draw(0,0);
}

void Viewport::update() {
  const float x = objectToTrack->X();
  const float y = objectToTrack->Y();
  position[0] = (x + objWidth/2) - viewWidth/2;
  position[1] = (y + objHeight/2) - viewHeight/2;
  if (position[0] < 0) position[0] = 0;
  if (position[1] < 0) position[1] = 0;
  if (position[0] > (worldWidth - viewWidth)) {
    position[0] = worldWidth-viewWidth;
  }
  if (position[1] > (worldHeight - viewHeight)) {
    position[1] = worldHeight-viewHeight;
  }
}
