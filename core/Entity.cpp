#include "Entity.h"

Entity::Entity() : vertices(sf::Quads, 4) {
  pos.x = 0;
  pos.y = 0;

  size.x = 10;
  size.y = 10;

  c = Color(0, 255, 0);

  isTextured = false;

  swapX = false;
  swapY = false;

  update();
}

Entity::Entity(Vector2f pos) : vertices(sf::Quads, 4) {
  this->pos.x = pos.x;
  this->pos.y = pos.y;

  size.x = 10;
  size.y = 10;

  c = Color(0, 255, 0);

  isTextured = false;

  swapX = false;
  swapY = false;

  update();
}

Entity::Entity(Vector2f pos, Vector2f size) : vertices(sf::Quads, 4) {
  this->pos.x = pos.x;
  this->pos.y = pos.y;

  this->size.x = size.x;
  this->size.y = size.y;

  c = Color(0, 255, 0);

  isTextured = false;

  swapX = false;
  swapY = false;

  update();
}

void Entity::setPos(Vector2f pos) {
  this->pos.x = pos.x;
  this->pos.y = pos.y;
  update();
}

void Entity::setSize(Vector2f size) {
  this->size.x = size.x;
  this->size.y = size.y;
  update();
}

void Entity::setColor(Color c) {
  this->c = c;
  update();
}

void Entity::setTexture(string path, string name, Vector2f tex_coord, Vector2f tex_size) {
  if(rm.addTexture(path, name, tex_coord, tex_size)) {

    isTextured = true;
    tex_name = name;

    this->tex_size = tex_size;

    rm.getTexture(tex_name)->setSmooth(true);
    c = Color(255, 255, 255);
  }

  update();
}

void Entity::setTexture(string name) {
  if(rm.getTexture(name) != NULL) {

    isTextured = true;
    tex_name = name;

    this->tex_size = rm.getTexSize(name);

    rm.getTexture(tex_name)->setSmooth(true);
    c = Color(255, 255, 255);
  }

  update();
}


Vector2f Entity::getPos() {
  return pos;
}

Vector2f Entity::getSize() {
  return size;
}

Color Entity::getColor() {
  return c;
}

string Entity::getTexture() {
  if (isTextured) {
    return tex_name;
  } else {
    return "null";
  }
}

Vector2f Entity::getTexSize() {
  if (isTextured) {
    return tex_size;
  } else {
    return Vector2f(0, 0);
  }
}

void Entity::update() {
  vertices[0].position = Vector2f(pos.x, pos.y);
  vertices[1].position = Vector2f(pos.x + size.x, pos.y);
  vertices[2].position = Vector2f(pos.x + size.x, pos.y + size.y);
  vertices[3].position = Vector2f(pos.x, pos.y + size.y);

  vertices[0].color = c;
  vertices[1].color = c;
  vertices[2].color = c;
  vertices[3].color = c;

  if (isTextured && !swapX && !swapY) {
    vertices[0].texCoords = Vector2f(0, 0);
    vertices[1].texCoords = Vector2f(tex_size.x , 0);
    vertices[2].texCoords = Vector2f(tex_size.x, tex_size.y);
    vertices[3].texCoords = Vector2f(0, tex_size.y);
  }

  if (isTextured && swapX && !swapY) {
    vertices[0].texCoords = Vector2f(tex_size.x, 0);
    vertices[1].texCoords = Vector2f(0, 0);
    vertices[2].texCoords = Vector2f(0, tex_size.y);
    vertices[3].texCoords = Vector2f(tex_size.x, tex_size.y);
  }

  if (isTextured && !swapX && swapY) {
    vertices[0].texCoords = Vector2f(0, tex_size.y);
    vertices[1].texCoords = Vector2f(tex_size.x , tex_size.y);
    vertices[2].texCoords = Vector2f(tex_size.x, 0);
    vertices[3].texCoords = Vector2f(0, 0);
  }

  if (isTextured && swapX && swapY) {
    vertices[0].texCoords = Vector2f(tex_size.x, tex_size.y);
    vertices[1].texCoords = Vector2f(0 , tex_size.y);
    vertices[2].texCoords = Vector2f(0, 0);
    vertices[3].texCoords = Vector2f(tex_size.x, 0);
  }
}

void Entity::draw(RenderWindow *window) {
  if (isTextured) {
    window->draw(vertices, rm.getTexture(tex_name));
  } else {
    window->draw(vertices);
  }
}

void Entity::scale (Vector2f prevSize, Vector2f actSize) {
  float x_factor = actSize.x / prevSize.x;
  float y_factor = actSize.y / prevSize.y ;

  pos.x *= x_factor;
  pos.y *= y_factor;

  size.x *= x_factor;
  size.y *= y_factor;

  update();
}

bool Entity::intersect(Vector2f p, Vector2f s) {
  bool intersectX = false;
  bool intersectY = false;

  if ((p.x >= pos.x && p.x <= pos.x + size.x) || (p.x + s.x >= pos.x && p.x + s.x <= pos.x + size.x))
    intersectX = true;

  if ((p.y >= pos.y && p.y <= pos.y + size.y) || (p.y + s.y >= pos.y && p.y + s.y <= pos.y + size.y))
    intersectY = true;

  if (intersectX && intersectY) {
    return true;
  } else {
    return false;
  }
}

bool Entity::intersectTop(Vector2f p, Vector2f s) {
  Vector2f p1 = Vector2f(pos.x + size.x / 4, pos.y + size.y / 8);
  Vector2f s1 = Vector2f(size.x / 2, size.y / 4);

  bool intersectX = false;
  bool intersectY = false;

  if ((p.x >= p1.x && p.x <= p1.x + s1.x) || (p.x + s.x >= p1.x && p.x + s.x <= p1.x + s1.x))
    intersectX = true;

  if ((p.y >= p1.y && p.y <= p1.y + s1.y) || (p.y + s.y >= p1.y && p.y + s.y <= p1.y + s1.y))
    intersectY = true;

  if (intersectX && intersectY) {
    return true;
  } else {
    return false;
  }

}

bool Entity::intersect(Entity e) {
  return intersect(e.getPos(), e.getSize());
}

void Entity::mirrorX() {
  swapX = !swapX;
  update();
}

void Entity::mirrorY() {
  swapY = !swapY;
  update();
}
