#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../core/Entity.h"
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

class Map {

public:
  Map(Vector2f tileSize, Vector2f mapSize);

  void load(string path);
  void genSecondaryFloors(int screenHeight);

  void setWorld(int world);

  void update();
  void draw(RenderWindow *window);

  void setPos(Vector2f p);
  void setSize(Vector2f s);

  vector<vector<Entity *>>* getGroundEntities();
  vector<vector<Entity *>>* getItemsEntities();

  Vector2f getPos();
  Vector2f getSize();

  void initGrid(string path);
  void updatePos();
  void updateSize();

  void hideItems(bool t);

  void clear();

private:
  int type;

  vector<vector<Entity *>> ground;
  vector<vector<Entity *>> player_level;
  vector<vector<vector<Entity *>>> sec_floor;

  Vector2f tileSize;
  Vector2f drawTileSize;

  bool showItems;

  Vector2f pos;
  Vector2f size;

  Vector2f box, grass, dirt, tree, table, y_box, ore, furnace, lock, puzzle, vd, water;

};

#endif
