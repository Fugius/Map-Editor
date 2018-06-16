#ifndef ENTITY
#define ENTITY

#include <iostream>
#include <SFML/Graphics.hpp>
#include "RessourceManager.h"

using namespace std;
using namespace sf;

class Entity {
public:
  Entity();
  Entity(Vector2f pos);
  Entity(Vector2f pos, Vector2f size);

  void setPos(Vector2f pos);
  void setSize(Vector2f size);
  void setColor(Color c);
  void setTexture(string path, string name, Vector2f tex_coord, Vector2f tex_size);
  void setTexture(string name);

  Vector2f getPos();
  Vector2f getSize();
  Color getColor();
  string getTexture();
  Vector2f getTexSize();

  void scale (Vector2f prevSize, Vector2f actSize);

  bool intersect(Entity e);
  bool intersect(Vector2f p, Vector2f s);

  bool intersectTop(Vector2f p, Vector2f s);

  void update();
  void draw(RenderWindow *window);

  void mirrorX();
  void mirrorY();

private:
  Vector2f pos;
  Vector2f size;

  VertexArray vertices;

  RessourceManager rm;
  string tex_name;
  Vector2f tex_size;

  Color c;
  bool isTextured;

  bool swapX;
  bool swapY;
};

#endif
