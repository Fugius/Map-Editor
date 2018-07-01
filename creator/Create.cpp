#include "Create.h"

Create::Create(Vector2f screenSize) {
  keyboardClock.restart();

  this->screenSize = screenSize;

  init = true;
  finished = false;
  groundEdit = true;
  world = 0;

  ta_size.setSize(Vector2f((screenSize.x * 0.75) * 0.7, screenSize.y / 15));
  ta_size.setPos(Vector2f(screenSize.x / 4 + screenSize.x * 0.75 * 0.15, screenSize.y / 2 - screenSize.y / 15 - 20));
  ta_size.setFont("ressources/fonts/Kenney Future.ttf");
  ta_size.enableButton(false);
  ta_size.setOnlyDigit(true);
  ta_size.setDefaultText("X : Map size (X * X)");
  ta_size.setBoxColor(Color(0, 0, 0, 175));

  ta_path.setSize(Vector2f((screenSize.x * 0.75) * 0.7, screenSize.y / 15));
  ta_path.setPos(Vector2f(screenSize.x / 4 + screenSize.x * 0.75 * 0.15, screenSize.y / 2 + 20));
  ta_path.setFont("ressources/fonts/Kenney Future.ttf");
  ta_path.setListener(this);
  ta_path.enableButton(true);
  ta_path.setDefaultText("Map path with name");
  ta_path.setBoxColor(Color(0, 0, 0, 175));
  ta_path.setButtonColor(Color(0, 0, 0, 175));

  int k = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      block_selection.push_back(new Entity);
      block_selection[k]->setPos(Vector2f((j + 1 ) * 10 + j * 93, (i + 1) * 20 + i * 106));
      block_selection[k]->setSize(Vector2f(93, 106));
      k++;
    }
  }

  background_selection.setPos(Vector2f(0, 0));
  background_selection.setSize(Vector2f(screenSize.x / 4, screenSize.y));
  background_selection.setColor(Color(0, 0, 0, 60));

  background.setPos(Vector2f(0, 0));
  background.setSize(screenSize);
  background.setTexture("ressources/placeholders/sky.png", "background", Vector2f(0, 0), Vector2f(1920, 1080));

  setSelection(0);



}

void Create::update(Event *event, RenderWindow *window) {
  //check inputs
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !init && !finished) {
    for (auto e : block_selection) {
      if (e->intersect(Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y), Vector2f(1, 1))) {
        currentTexture = e->getTexture();
      }
    }
  }

  if (keyboardClock.getElapsedTime().asMilliseconds() >= 500 && !init && !finished) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
      groundEdit = !groundEdit;
      map->hideItems(groundEdit);
      keyboardClock.restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
      world = 0;
      RessourceManager::clear();
      background.setTexture("ressources/placeholders/sky.png", "background", Vector2f(0, 0), Vector2f(1920, 1080));
      setSelection(0);
      saveMap(true);
      map->clear();
      delete map;
      map = new Map(Vector2f(222, 256), Vector2f(screenSize.x * 0.75 * 0.8, (9/16) * screenSize.x * 0.75 * 0.8));
      map->load(path);
      map->setSize(Vector2f(screenSize.x * 0.75 * 0.8, 0.5625 * screenSize.x * 0.75 * 0.8));
      map->setPos(Vector2f(screenSize.x * 0.25 + screenSize.x * 0.075, screenSize.y / 2 - map->getSize().y / 2));
      map->genSecondaryFloors(screenSize.y);
      map->hideItems(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
      world = 1;
      setSelection(1);
      saveMap(true);
      map->clear();
      delete map;
      map = new Map(Vector2f(222, 256), Vector2f(screenSize.x * 0.75 * 0.8, (9/16) * screenSize.x * 0.75 * 0.8));
      map->load(path);
      map->setSize(Vector2f(screenSize.x * 0.75 * 0.8, 0.5625 * screenSize.x * 0.75 * 0.8));
      map->setPos(Vector2f(screenSize.x * 0.25 + screenSize.x * 0.075, screenSize.y / 2 - map->getSize().y / 2));
      map->genSecondaryFloors(screenSize.y);
      map->hideItems(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
      world = 2;
      setSelection(2);
      saveMap(true);
      map->clear();
      delete map;
      map = new Map(Vector2f(222, 256), Vector2f(screenSize.x * 0.75 * 0.8, (9/16) * screenSize.x * 0.75 * 0.8));
      map->load(path);
      map->setSize(Vector2f(screenSize.x * 0.75 * 0.8, 0.5625 * screenSize.x * 0.75 * 0.8));
      map->setPos(Vector2f(screenSize.x * 0.25 + screenSize.x * 0.075, screenSize.y / 2 - map->getSize().y / 2));
      map->genSecondaryFloors(screenSize.y);
      map->hideItems(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
      world = 3;
      setSelection(3);
      saveMap(true);
      map->clear();
      delete map;
      map = new Map(Vector2f(222, 256), Vector2f(screenSize.x * 0.75 * 0.8, (9/16) * screenSize.x * 0.75 * 0.8));
      map->load(path);
      map->setSize(Vector2f(screenSize.x * 0.75 * 0.8, 0.5625 * screenSize.x * 0.75 * 0.8));
      map->setPos(Vector2f(screenSize.x * 0.25 + screenSize.x * 0.075, screenSize.y / 2 - map->getSize().y / 2));
      map->genSecondaryFloors(screenSize.y);
      map->hideItems(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
      keyboardClock.restart();
      saveMap(false);
      map->clear();
      map = new Map(Vector2f(222, 256), Vector2f(screenSize.x * 0.75 * 0.8, (9/16) * screenSize.x * 0.75 * 0.8));
      map->load(path);
      map->setSize(Vector2f(screenSize.x * 0.75 * 0.8, 0.5625 * screenSize.x * 0.75 * 0.8));
      map->setPos(Vector2f(screenSize.x * 0.25 + screenSize.x * 0.075, screenSize.y / 2 - map->getSize().y / 2));
      map->genSecondaryFloors(screenSize.y);
      finished = true;
    }

  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && groundEdit && !init && !finished) {
    for (auto a : *map->getGroundEntities()) {
      for (auto b : a) {
        if (b->intersectTop(Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y), Vector2f(1, 1))) {
          b->setTexture(currentTexture);
        }
      }
    }
  } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !init && !finished) {
    for (auto a : *map->getItemsEntities()) {
      for (auto b : a) {
        if (b->intersectTop(Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y), Vector2f(1, 1))) {
          b->setTexture(currentTexture);
        }
      }
    }
  }

  background.update();
  background_selection.update();

  if (init) {
    ta_size.pollEvent(event, window);
    ta_size.update(window);

    ta_path.pollEvent(event, window);
    ta_path.update(window);
  } else {
    map->update();
  }

  for (int i = 0; i < block_selection.size(); i++) {
    block_selection[i]->update();
  }

}

void Create::draw(RenderWindow *window) {
  background.draw(window);
  background_selection.draw(window);

  if (init) {
    ta_path.draw(window);
    ta_size.draw(window);
  } else {
    map->draw(window);
  }

  for (int i = 0; i < block_selection.size(); i++) {
    block_selection[i]->draw(window);
  }
}

void Create::setSelection(int world) {
  Vector2f tileSize = Vector2f(222, 256);

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

  block_selection[0]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "grass", Vector2f(grass.x * tileSize.x, grass.y * tileSize.y), tileSize);
  block_selection[1]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "water", Vector2f(water.x * tileSize.x, water.y * tileSize.y), tileSize);
  block_selection[2]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "dirt", Vector2f(dirt.x * tileSize.x, dirt.y * tileSize.y), tileSize);
  block_selection[3]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "box", Vector2f(box.x * tileSize.x, box.y * tileSize.y), tileSize);
  block_selection[4]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "tree", Vector2f(tree.x * tileSize.x, tree.y * tileSize.y), tileSize);
  block_selection[5]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "table", Vector2f(table.x * tileSize.x, table.y * tileSize.y), tileSize);
  block_selection[6]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "y_box", Vector2f(y_box.x * tileSize.x, y_box.y * tileSize.y), tileSize);
  block_selection[7]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "ore", Vector2f(ore.x * tileSize.x, ore.y * tileSize.y), tileSize);
  block_selection[8]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "furnace", Vector2f(furnace.x * tileSize.x, furnace.y * tileSize.y), tileSize);
  block_selection[9]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "lock", Vector2f(lock.x * tileSize.x, lock.y * tileSize.y), tileSize);
  block_selection[10]->setTexture("ressources/tiles/tilesheet_complete_2X.png", "puzzle", Vector2f(puzzle.x * tileSize.x, puzzle.y * tileSize.y), tileSize);
  block_selection[11]->setTexture("ressources/tiles/placeHolder.png", "blank", Vector2f(0, 0), tileSize);
}

void Create::onClickListener(TextArea *area) {
  int size = stoi(ta_size.getText());
  string p = ta_path.getText();

  genBlankMap(p, size, size);

  init = false;

  map = new Map(Vector2f(222, 256), Vector2f(screenSize.x * 0.75 * 0.8, (9/16) * screenSize.x * 0.75 * 0.8));
  map->load(p);
  map->setSize(Vector2f(screenSize.x * 0.75 * 0.8, 0.5625 * screenSize.x * 0.75 * 0.8));
  map->setPos(Vector2f(screenSize.x * 0.25 + screenSize.x * 0.075, screenSize.y / 2 - map->getSize().y / 2));
  map->genSecondaryFloors(screenSize.y);

  map->hideItems(true);
}

void Create::genBlankMap(string name, int w, int h) {
  ofstream str;
  str.open(name, ofstream::out | ofstream::trunc);

  path = name;
  size = w;

  if (str.bad()) {
    cout << "Error opening stream : " << name << endl;
  }

  str << "0\n#\n";

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      str << "E";
    }
    str << "\n";
  }

  str << "#\n";

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      str << "E";
    }
    str << "\n";
  }

  str.close();
}

void Create::clear() {
  map->clear();
}

void Create::saveMap(bool editing) {
  ofstream str;
  str.open(path, ofstream::out | ofstream::trunc);

  str << world << "\n" << "#" << "\n";

  for (int i = 0; i < (*map->getGroundEntities())[0].size(); i++) {
    for (int j = 0; j < map->getGroundEntities()->size(); j++) {

      Entity *b = (*map->getGroundEntities())[j][i];

      if (b->getTexture() == "blank" && !editing)
        str << "V";

      if (b->getTexture() == "blank" && editing)
        str << "E";

      if (b->getTexture() == "grass")
        str << "G";

      if (b->getTexture() == "water")
        str << "W";

      if (b->getTexture() == "dirt")
        str << "D";

      if (b->getTexture() == "box")
        str << "B";

      if (b->getTexture() == "tree")
        str << "T";

      if (b->getTexture() == "table")
        str << "U";

      if (b->getTexture() == "y_box")
        str << "Y";

      if (b->getTexture() == "ore")
        str << "O";

      if (b->getTexture() == "furnace")
        str << "F";

      if (b->getTexture() == "lock")
        str << "L";

      if (b->getTexture() == "puzzle")
        str << "P";

    }

    str << "\n";
  }

  str << "#" << "\n";

  for (int i = 0; i < (*map->getItemsEntities())[0].size(); i++) {
    for (int j = 0; j < map->getItemsEntities()->size(); j++) {

      Entity *b = (*map->getItemsEntities())[j][i];

      if (b->getTexture() == "blank" && !editing)
        str << "V";

      if (b->getTexture() == "blank" && editing)
        str << "E";

      if (b->getTexture() == "grass")
        str << "G";

      if (b->getTexture() == "water")
        str << "W";

      if (b->getTexture() == "dirt")
        str << "D";

      if (b->getTexture() == "box")
        str << "B";

      if (b->getTexture() == "tree")
        str << "T";

      if (b->getTexture() == "table")
        str << "U";

      if (b->getTexture() == "y_box")
        str << "Y";

      if (b->getTexture() == "ore")
        str << "O";

      if (b->getTexture() == "furnace")
        str << "F";

      if (b->getTexture() == "lock")
        str << "L";

      if (b->getTexture() == "puzzle")
        str << "P";

    }
    str << "\n";
  }

  str.close();
}
