#ifndef TEXT_AREA
#define TEXT_AREA

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../core/Entity.h"
#include "../listeners/TextAreaListener.h"
#include <stdio.h>
#include <ctype.h>

using namespace std;
using namespace sf;

class TextAreaListener;

class TextArea {
public:
  TextArea();

  void setSize(Vector2f s);
  void setPos(Vector2f pos);
  void setListener(TextAreaListener *listener);
  void setDefaultText(string d);
  void setButtonColor(Color c);
  void setFont(string f);
  void setBoxColor(Color c);

  Vector2f getSize();
  Vector2f getPos();
  string getText();

  void update(RenderWindow *window);
  void draw(RenderWindow *window);
  void scale(Vector2f oldSize, Vector2f newSize);

  void pollEvent(Event *event, RenderWindow *window);

  void updateText();
  void updateButton();

  void enableButton(bool b);

  void setError(string s);
  void setOnlyDigit(bool b);

private:
  RectangleShape textBox;
  RectangleShape b_bg;
  Entity Button;

  Text text;
  string defaultText;
  int max_size;
  string text_input;

  Color buttonColor;
  Font font;
  Color boxColor;
  Color defaultColor;

  bool hasButton;
  bool font_set;

  TextAreaListener *callback;
  bool isSelect;

  bool onlyDigit;
};

#endif
