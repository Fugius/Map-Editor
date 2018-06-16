#ifndef TEXT_AREA_LISTENER_H
#define TEXT_AREA_LISTENER_H

#include <iostream>
#include "../base/TextArea.h"

class TextArea;

class TextAreaListener {
  public:
    virtual void onClickListener(TextArea *area) {

    };

    ~TextAreaListener() {
      //nothing
    };
};

#endif
