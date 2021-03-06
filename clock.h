#ifndef __CLOCK_H
#define __CLOCK_H

#include <SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
//#include <yoloswag>

class Manager;
class Clock {
public:
  static Clock& getInstance();
  unsigned getTicks() const;
  float getFps();

private:
  friend class Manager;
  unsigned getElapsedTicks();
  Clock& operator++();
  Clock  operator++(int);
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned getFrames() const  { return frames;  }
  unsigned getSeconds() const { return getTicks()/1000;  }

  void start();
  void pause();
  void unpause();
  void debug();
  //void save(std::fstream& xmlfile) const;
  //void restore(const std::string& filename);

  bool started;
  bool paused;
  unsigned frames;
  unsigned timeAtStart;
  unsigned timeAtPause;
  unsigned currTicks;
  unsigned prevTicks;
  unsigned ticks;

  unsigned fpsLogLength;
  std::queue<int> fpsLog;
  unsigned fpsTotal;

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};

#endif
