#ifndef CREATE
#define CREATE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "../map/Map.h"
#include "../base/TextArea.h"


using namespace std;
using namespace sf;

class Create : public TextAreaListener {

public:
  Create(Vector2f screenSize);

  void update(Event *event, RenderWindow *window);
  void draw(RenderWindow *window);

  void setSelection(int world);
  void onClickListener(TextArea *area);

  void genBlankMap(string name, int w, int h);

  void saveMap(bool editing);

  void clear();

private:
  Map *map;

  TextArea ta_size;
  TextArea ta_path;

  string path;
  int size;

  string currentTexture;

  bool init;
  bool finished;
  bool groundEdit;

  Clock keyboardClock;

  int world;

  Vector2f screenSize;

  vector<Entity *> block_selection;
  Entity background_selection;
  Entity background;

  Vector2f box, grass, dirt, tree, table, y_box, ore, furnace, lock, puzzle, vd, water;

};

#endif
