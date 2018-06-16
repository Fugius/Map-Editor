#include "Map.h"

Map::Map(Vector2f tileSize, Vector2f mapSize) {

  this->tileSize = tileSize;
  size = mapSize;

  showItems = true;

  pos = Vector2f(0, 0);

}

void Map::setWorld(int world) {
  if (world == 0) {
    box = Vector2f(5, 3);
    grass = Vector2f(0, 0);
    dirt = Vector2f(1, 0);
    tree = Vector2f(16, 1);

    table = Vector2f(19, 1);
    y_box = Vector2f(5, 2);
    ore = Vector2f(15, 3);

    furnace = Vector2f(18, 1);
    lock = Vector2f(7, 4);

    puzzle = Vector2f(7, 6);
    water = Vector2f(8, 6);
  }

  if (world == 1) {
    box = Vector2f(5, 3);
    grass = Vector2f(14, 0);
    dirt = Vector2f(10, 0);
    tree = Vector2f(15, 1);

    table = Vector2f(19, 1);
    y_box = Vector2f(5, 2);
    ore = Vector2f(15, 3);

    furnace = Vector2f(18, 1);
    lock = Vector2f(7, 4);

    puzzle = Vector2f(7, 6);
    water = Vector2f(8, 6);
  }

  if (world == 2) {
    box = Vector2f(5, 3);
    grass = Vector2f(6, 0);
    dirt = Vector2f(7, 0);
    tree = Vector2f(15, 1);

    table = Vector2f(19, 1);
    y_box = Vector2f(5, 2);
    ore = Vector2f(15, 3);

    furnace = Vector2f(18, 1);
    lock = Vector2f(7, 4);

    puzzle = Vector2f(7, 6);
    water = Vector2f(8, 6);
  }

  if (world == 3) {
    box = Vector2f(5, 3);
    grass = Vector2f(6, 2);
    dirt = Vector2f(7, 2);
    tree = Vector2f(15, 1);

    table = Vector2f(19, 1);
    y_box = Vector2f(5, 2);
    ore = Vector2f(15, 3);

    furnace = Vector2f(18, 1);
    lock = Vector2f(7, 4);

    puzzle = Vector2f(7, 6);
    water = Vector2f(3, 4);
  }
}

void Map::initGrid(string path) {
  ifstream stream(path);
  string line;

  int w = 0;
  int h = 0;

  if (stream.bad()) {
    cout << "Impossible to load map" << path << endl;
  }

  getline(stream, line);
  setWorld(stoi(line));
  getline(stream, line);

  while (getline(stream, line)) {

    if (line[0] == '#') {
      break;
    } else {
      w = line.size();
      h++;
    }

  }


  for (int i = 0; i < w; i++) {
    vector<Entity *> temp;
    ground.push_back(temp);

    vector<Entity *> tempa;
    player_level.push_back(tempa);

    for (int j = 0; j < h; j++) {
      ground[i].push_back(new Entity);
      player_level[i].push_back(new Entity);

    }

  }

  drawTileSize.x = sqrt((size.x + size.y) / 2) / (int) sqrt((h + w) / 2);
  drawTileSize.y = sqrt((size.x + size.y) / 2) / (int) sqrt((h + w) / 2);

  stream.close();
}

void Map::load(string path) {
  initGrid(path);

  int floor = 0;
  int y = 0;
  string line;

  ifstream stream(path);

  if (stream.bad()) {
    cout << "Impossible to load map" << path << endl;
  } else {
    getline(stream, line);
    getline(stream, line);
    while (getline(stream, line)) {
      if (floor == 0) {
        if (line[0] == '#') {
          floor++;
          y = 0;
          continue;
        }

        for (int i = 0; i < line.size(); i++) {
          if (line[i] == 'B')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "box", Vector2f(box.x * tileSize.x, box.y * tileSize.y), tileSize);

          if (line[i] == 'T')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "tree", Vector2f(tree.x * tileSize.x, tree.y * tileSize.y), tileSize);

          if (line[i] == 'U')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "table", Vector2f(table.x * tileSize.x, table.y * tileSize.y), tileSize);

          if (line[i] == 'Y')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "y_box", Vector2f(y_box.x * tileSize.x, y_box.y * tileSize.y), tileSize);

          if (line[i] == 'O')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "ore", Vector2f(ore.x * tileSize.x, ore.y * tileSize.y), tileSize);

          if (line[i] == 'F')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "furnace", Vector2f(furnace.x * tileSize.x, furnace.y * tileSize.y), tileSize);

          if (line[i] == 'L')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "lock", Vector2f(lock.x * tileSize.x, lock.y * tileSize.y), tileSize);

          if (line[i] == 'P')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "puzzle", Vector2f(puzzle.x * tileSize.x, puzzle.y * tileSize.y), tileSize);

          if (line[i] == 'G')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "grass", Vector2f(grass.x * tileSize.x, grass.y * tileSize.y), tileSize);

          if (line[i] == 'W')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "water", Vector2f(water.x * tileSize.x, water.y * tileSize.y), tileSize);

          if (line[i] == 'D')
            ground[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "dirt", Vector2f(dirt.x * tileSize.x, dirt.y * tileSize.y), tileSize);

          if (line[i] == 'E')
            ground[i][y]->setTexture("ressources/tiles/placeHolder.png", "blank", Vector2f(0, 0), tileSize);

          if (line[i] == 'V') {
            ground[i][y]->setColor(Color(0, 0, 0, 0));
          }
        }
      } else {
        for (int i = 0; i < line.size(); i++) {
          if (line[i] == 'G')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "grass", Vector2f(grass.x * tileSize.x, grass.y * tileSize.y), tileSize);

          if (line[i] == 'W')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "water", Vector2f(water.x * tileSize.x, water.y * tileSize.y), tileSize);

          if (line[i] == 'D')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "dirt", Vector2f(dirt.x * tileSize.x, dirt.y * tileSize.y), tileSize);

          if (line[i] == 'B')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "box", Vector2f(box.x * tileSize.x, box.y * tileSize.y), tileSize);

          if (line[i] == 'T')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "tree", Vector2f(tree.x * tileSize.x, tree.y * tileSize.y), tileSize);

          if (line[i] == 'U')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "table", Vector2f(table.x * tileSize.x, table.y * tileSize.y), tileSize);

          if (line[i] == 'Y')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "y_box", Vector2f(y_box.x * tileSize.x, y_box.y * tileSize.y), tileSize);

          if (line[i] == 'O')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "ore", Vector2f(ore.x * tileSize.x, ore.y * tileSize.y), tileSize);

          if (line[i] == 'F')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "furnace", Vector2f(furnace.x * tileSize.x, furnace.y * tileSize.y), tileSize);

          if (line[i] == 'L')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "lock", Vector2f(lock.x * tileSize.x, lock.y * tileSize.y), tileSize);

          if (line[i] == 'P')
            player_level[i][y]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "puzzle", Vector2f(puzzle.x * tileSize.x, puzzle.y * tileSize.y), tileSize);

          if (line[i] == 'E')
            player_level[i][y]->setTexture("ressources/tiles/placeHolder.png", "blank", Vector2f(0, 0), tileSize);

          if (line[i] == 'V')
            player_level[i][y]->setColor(Color(0, 0, 0, 0));
        }
      }
      y++;
    }
  }

  setSize(size);

  updateSize();
  updatePos();


}

void Map::updatePos() {
  if (ground[ground.size() - 1][0]->getPos().x == pos.x && ground[0][0]->getPos().y == pos.y) {
    return;
  }

  float x_decal = pos.x - ground[0][ground.size() - 1]->getPos().x;
  float y_decal = pos.y - ground[0][0]->getPos().y;

  for (int i = 0; i < ground.size(); i++) {
    for (int j = 0; j < ground[0].size(); j++) {
      ground[j][i]->setPos(Vector2f(ground[j][i]->getPos().x + x_decal, ground[j][i]->getPos().y + y_decal));
      player_level[j][i]->setPos(Vector2f(player_level[j][i]->getPos().x + x_decal, player_level[j][i]->getPos().y + y_decal));
    }
  }


}

void Map::updateSize() {
  float y_decal = 0;
  float x_decal = 0;

  for (int i = 0; i < ground.size(); i++) {
    y_decal = i * (drawTileSize.y / 4) + 1;
    x_decal = -i * (drawTileSize.x / 2) + 1;
    for (int j = 0; j < ground[0].size(); j++) {
      ground[j][i]->setPos(Vector2f(x_decal + j * drawTileSize.x / 2 , y_decal ));
      ground[j][i]->setSize(drawTileSize);
      y_decal += drawTileSize.y / 4;
    }
  }

  for (int i = 0; i < player_level.size(); i++) {
    for (int j = 0; j < player_level[0].size(); j++) {

      player_level[j][i]->setSize(Vector2f(ground[j][i]->getSize().x * 0.6, ground[j][i]->getSize().y * 0.6));
      float xpos = ground[j][i]->getPos().x + (ground[j][i]->getSize().x / 2) - (player_level[j][i]->getSize().x / 2);
      float ypos = ground[j][i]->getPos().y + (ground[j][i]->getSize().y / 2) - player_level[j][i]->getSize().y - (((ground[j][i]->getSize().y / 2) - (player_level[j][i]->getSize().y / 2)) / 2);
      player_level[j][i]->setPos(Vector2f(xpos, ypos));

    }
  }

  for (auto a : sec_floor) {
    for (int i = 0; i < a.size(); i++) {
      for (int j = 0; j < a[0].size(); j++) {
        a[j][i]->setSize(Vector2f(ground[j][i]->getSize().x, ground[j][i]->getSize().y));
      }
    }
  }

  updatePos();
}

void Map::update() {
  updatePos();
  updateSize();

  for (auto a : sec_floor) {
    for (auto b : a) {
      for (auto c : b) {
        c->update();
      }
    }
  }

  for (auto v : ground) {
    for (auto e : v) {
      e->update();
    }
  }

  if (showItems) {
    for (auto v : player_level) {
      for (auto e : v) {
        e->update();
      }
    }
  }
}

void Map::draw(RenderWindow *window) {

  for (int a = sec_floor.size() - 1; a > -1; a--) {
    sec_floor[a][0][0]->draw(window);

    for (int i = 1; i < sec_floor[a].size(); i++) {
      for (int j = 0; j < i; j++) {
        sec_floor[a][i][j]->draw(window);
        sec_floor[a][j][i]->draw(window);
      }
      sec_floor[a][i][i]->draw(window);
    }
  }


  ground[0][0]->draw(window);

  for (int i = 1; i < ground.size(); i++) {
    for (int j = 0; j < i; j++) {
      ground[i][j]->draw(window);
      ground[j][i]->draw(window);
    }
    ground[i][i]->draw(window);
  }


  if (showItems) {
    player_level[0][0]->draw(window);

    for (int i = 1; i < player_level.size(); i++) {
      for (int j = 0; j < i; j++) {
        player_level[i][j]->draw(window);
        player_level[j][i]->draw(window);
      }
      player_level[i][i]->draw(window);
    }
  }

}

void Map::clear() {
  for (auto a : ground) {
    for (auto b : a) {
      delete b;
    }
  }

  for (auto a : player_level) {
    for (auto b : a) {
      delete b;
    }
  }

  while (ground.size() > 0 || player_level.size() > 0) {
    ground.pop_back();
    player_level.pop_back();
  }
}

void Map::setPos(Vector2f p) {
  pos = p;
  updatePos();
}

void Map::setSize(Vector2f s) {
  size = s;

  drawTileSize.x = s.x / (ground.size() >= ground[0].size() ? ground.size() : ground[0].size());
  drawTileSize.y = 2*s.y / ((ground.size() >= ground[0].size() ? ground.size() : ground[0].size())+1);

  updateSize();
}

void Map::genSecondaryFloors(int screenHeight) {
  int fillerNumber = (screenHeight - (size.y / 2) + pos.y) / (drawTileSize.y * 0.4) + 1;
  int k = 0;

  for (int i = 0; i < fillerNumber; i++) {
    vector<vector<Entity *>>temp;
    sec_floor.push_back(temp);
  }

  for (int e = 0; e < sec_floor.size(); e++) {

    for (auto x : ground) {
      vector<Entity *> temp;
      sec_floor[e].push_back(temp);
      for (auto y : x) {
        sec_floor[e][sec_floor[e].size() - 1].push_back(new Entity);
      }
    }

    for (int i = 0; i < sec_floor[e].size(); i++) {
      for (int j = 0; j < sec_floor[e][i].size(); j++) {
        sec_floor[e][i][j]->setSize(ground[i][j]->getSize());
        sec_floor[e][i][j]->setPos(Vector2f(ground[i][j]->getPos().x, ground[i][j]->getPos().y + (k + 1) * (drawTileSize.y * 0.5)));

        if (ground[i][j]->getColor().a == 0) {
          sec_floor[e][i][j]->setColor(Color(0, 0, 0, 0));
        } else if (ground[i][j]->getTexture() == "grass") {
          sec_floor[e][i][j]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "dirt", Vector2f(dirt.x * tileSize.x, dirt.y * tileSize.y), tileSize);
        } else {
          sec_floor[e][i][j]->setTexture(ground[i][j]->getTexture());
        }
      }
    }
    k++;
  }

}


Vector2f Map::getPos() {
  return pos;
}

Vector2f Map::getSize() {
  return size;
}

vector<vector<Entity *>>* Map::getGroundEntities() {
  return &ground;
}

vector<vector<Entity *>>* Map::getItemsEntities() {
  return &player_level;
}

void Map::hideItems(bool t) {
  showItems = !t;
}
