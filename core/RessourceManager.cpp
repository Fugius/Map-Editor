#include "RessourceManager.h"

std::vector<tex*> RessourceManager::textures;

RessourceManager::RessourceManager() {

}

Texture* RessourceManager::getTexture(string path) {
  for (auto t : RessourceManager::textures) {
    if (t->name == path) {
      return &(t->data);
    }
  }

  return NULL;
}

bool RessourceManager::addTexture(string path, string name, Vector2f pos, Vector2f size) {

  for (auto t : RessourceManager::textures) {
    if (t->name == name && (size.x == t->data.getSize().x && size.y == t->data.getSize().y) && t->pos == pos) {
      return true;
    } else if (t->name == name) {
      if (!t->data.loadFromFile(path, IntRect(pos.x, pos.y, size.x, size.y))) {
        cout << "Can't load file " << path << endl;
        return false;
      } else {
        t->pos = pos;
        return true;
      }
    }
  }

  RessourceManager::textures.push_back(new tex);
  RessourceManager::textures[(RessourceManager::textures.size() - 1)]->name = name;
  RessourceManager::textures[(RessourceManager::textures.size() - 1)]->pos = pos;

  if (!RessourceManager::textures[(RessourceManager::textures.size() - 1)]->data.loadFromFile(path, IntRect(pos.x, pos.y, size.x, size.y))) {
    cout << "Can't load file " << path << endl;
    delete RessourceManager::textures[(RessourceManager::textures.size() - 1)];
    RessourceManager::textures.pop_back();
    return false;
  }

  return true;
}

bool RessourceManager::addTexture(string path, string name) {

  for (auto t : RessourceManager::textures) {
    if (t->name == name)
      return true;
  }

  RessourceManager::textures.push_back(new tex);
  RessourceManager::textures[(RessourceManager::textures.size() - 1)]->name = name;

  if (!RessourceManager::textures[(RessourceManager::textures.size() - 1)]->data.loadFromFile(path)) {
    cout << "Can't load file " << path << endl;
    delete RessourceManager::textures[(RessourceManager::textures.size() - 1)];
    RessourceManager::textures.pop_back();
    return false;
  }

  return true;
}

void RessourceManager::clear() {
  for (auto t : RessourceManager::textures) {
    delete t;
    t = NULL;
  }

  while (RessourceManager::textures.size() > 0) {
    RessourceManager::textures.pop_back();
  }

  cout << "Ressource manager cleared" << endl;

}

RessourceManager::~RessourceManager() {

}

Vector2f RessourceManager::getTexSize(string name) {
  for (auto t : RessourceManager::textures) {
    if (t->name == name)
      return Vector2f(t->data.getSize().x, t->data.getSize().y);
  }

  return Vector2f(0, 0);
}
