#ifndef RESSOURCE_MANAGER
#define RESSOURCE_MANAGER

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

typedef struct tex {
  string name;
  Texture data;
  Vector2f pos;
} tex;

class RessourceManager {
public:
  RessourceManager();

  Texture* getTexture(string name);
  bool addTexture(string path, string name, Vector2f pos, Vector2f size);
  bool addTexture(string path, string name);

  Vector2f getTexSize(string name);

  void static clear();
  ~RessourceManager();

private:
  static std::vector<tex*> textures;
};

#endif
