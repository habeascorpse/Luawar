#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <guichan.hpp>
#include <guichan/sdl.hpp>

class Button:public gcn::Button {

  public:

  Button(string caption) : gcn::Button(caption) {
    click = false;
  }

  virtual void mousePressed(gcn::MouseEvent& mouseEvent) {
    click = true;
  }

  bool click;

};



#endif // BUTTON_H_INCLUDED
