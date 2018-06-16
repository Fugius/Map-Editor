#include "TextArea.h"

TextArea::TextArea() {
  hasButton = false;
  font_set = false;
  isSelect = false;
  onlyDigit = false;

  max_size = 0;
  text_input = "";

  textBox.setSize(Vector2f(100, 50));
  textBox.setPosition(Vector2f(0, 0));
  textBox.setFillColor(Color(0, 0, 0, 15));
  textBox.setOutlineThickness(1);
  textBox.setOutlineColor(Color(0, 0, 0));

  defaultText = "DEFAULT";
  text.setString(defaultText);
  defaultColor = Color(86, 86, 86, 200);
  text.setFillColor(defaultColor);
  text.setCharacterSize(textBox.getSize().y * 0.75);
  updateText();

  buttonColor = Color(0, 255, 0, 130);
  boxColor = Color::Green;

  updateButton();
  Button.setTexture("ressources/ui/sheet_white1x.png", "arrow",  Vector2f(8, 461), Vector2f(34, 28));

}

void TextArea::setSize(Vector2f s) {
  textBox.setSize(s);
  updateText();
  updateButton();
}

void TextArea::setPos(Vector2f pos) {
  textBox.setPosition(pos);
  updateText();
  updateButton();
}


void TextArea::setListener(TextAreaListener *listener) {
  callback = listener;
}


void TextArea::setDefaultText(string d) {
  defaultText = d;
  text.setString(d);
  updateText();
}

void TextArea::setButtonColor(Color c) {
  buttonColor = Color(c.r, c.g, c.b, 230);
  updateButton();
}

void TextArea::setFont(string f) {
  if (font.loadFromFile(f)) {
      font_set = true;
      text.setFont(font);
      updateText();
  }
}

void TextArea::updateText() {
  float text_size = text.getLocalBounds().width;

  if (!hasButton && text.getLocalBounds().width < textBox.getSize().x) {
    text.setPosition(Vector2f(textBox.getPosition().x + textBox.getSize().x - text_size * 1.05, textBox.getPosition().y + textBox.getSize().y * 0.125));
    textBox.setOutlineColor(boxColor);

  } else if (hasButton && text.getLocalBounds().width < (textBox.getSize().x - b_bg.getSize().x)) {
    text.setPosition(Vector2f(textBox.getPosition().x + textBox.getSize().x - b_bg.getSize().x * 1.5 - text_size, b_bg.getPosition().y + b_bg.getSize().y * 0.125));
    textBox.setOutlineColor(boxColor);
  } else {
    if (max_size == 0) {
      max_size = static_cast<int>(text.getString().getSize());
      if (text_input == "") {
        text.setString(defaultText.substr(0, max_size - 3) + "...");
      } else {
        text.setString(text_input.substr(0, max_size - 3) + "...");
      }
    } else {
      if (text_input == "") {
        text.setString(defaultText.substr(0, max_size - 3) + "...");
      } else {
        text.setString(text_input.substr(0, max_size - 3) + "...");
      }
      text.setPosition(Vector2f(textBox.getPosition().x + textBox.getSize().x - b_bg.getSize().x * 1.5 - text_size, b_bg.getPosition().y + b_bg.getSize().y * 0.125));
    }

    if (hasButton) {
      text.setPosition(Vector2f(textBox.getPosition().x + textBox.getSize().x - b_bg.getSize().x * 1.5 - text_size, b_bg.getPosition().y + b_bg.getSize().y * 0.125));
    } else {
      text.setPosition(Vector2f(textBox.getPosition().x + textBox.getSize().x - text_size * 1.05, textBox.getPosition().y + textBox.getSize().y * 0.125));
    }
  }

  text.setPosition(text.getPosition().x, text.getPosition().y - text.getLocalBounds().top);

}

void TextArea::enableButton(bool b) {
  hasButton = b;
}

void TextArea::updateButton() {
    b_bg.setPosition(Vector2f(textBox.getPosition().x + textBox.getSize().x - textBox.getSize().y, textBox.getPosition().y));
    b_bg.setSize(Vector2f(textBox.getSize().y, textBox.getSize().y));
    b_bg.setFillColor(buttonColor);
    b_bg.setOutlineThickness(1);
    b_bg.setOutlineColor(boxColor);

    Button.setPos(Vector2f(b_bg.getPosition().x + b_bg.getSize().x * 0.1, b_bg.getPosition().y + b_bg.getSize().y * 0.1));
    Button.setSize(Vector2f(b_bg.getSize().x * 0.8, b_bg.getSize().y * 0.8));

}

void TextArea::pollEvent(Event *event, RenderWindow *window) {
  if (event->type == sf::Event::TextEntered && isSelect) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
      for (int i = 0; i < sf::Clipboard::getString().getSize(); i++) {
        if (!isdigit(sf::Clipboard::getString()[i]))
          return;
      }
      text_input += sf::Clipboard::getString();
      text.setString(text_input);
      updateText();
    }

    if (onlyDigit && (!isdigit(event->text.unicode))) {
      if (event->text.unicode != '\b')
        return;
    }

    if (event->text.unicode == '\b') {
      if (text_input.length() == 1) {
        text_input = "";
      } else if (text_input.length() > 0) {
        text_input = text_input.substr(0, text_input.length() - 1);
      }
      text.setString(text_input);
      updateText();
    } else if (hasButton && (event->text.unicode == '\n' || event->text.unicode == '\r\n' || event->text.unicode == '\r')) {
      callback->onClickListener(this);
    }else if (event->text.unicode < 128 && isprint(static_cast<char>(event->text.unicode)) && text_input.length() <= 20 && (event->text.unicode != '\n' || event->text.unicode != '\r\n' || event->text.unicode != '\r')) {
      text_input += static_cast<char>(event->text.unicode);
      text.setString(text_input);
      updateText();
    } else {
      updateText();
      textBox.setOutlineColor(Color::Red);
    }
  }

  if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
    if (hasButton && b_bg.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
      b_bg.setFillColor(Color(b_bg.getFillColor().r, b_bg.getFillColor().g, b_bg.getFillColor().b, 200));
      callback->onClickListener(this);
    } else {
      b_bg.setFillColor(Color(b_bg.getFillColor().r, b_bg.getFillColor().g, b_bg.getFillColor().b, 130));
    }
  }
}

void TextArea::update(RenderWindow *window) {
  if (text_input == "") {
    text.setString(defaultText);
    text.setFillColor(defaultColor);
  } else {
    text.setFillColor(Color::Black);
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (textBox.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
        textBox.setOutlineThickness(3);
        textBox.setOutlineColor(boxColor);
        isSelect = true;
      } else {
        textBox.setOutlineThickness(1);
        textBox.setOutlineColor(Color::Black);
        isSelect = false;
      }
  }

  updateText();

}

void TextArea::draw(RenderWindow *window) {
  if (hasButton) {
    window->draw(textBox);
    window->draw(b_bg);
    Button.draw(window);
    if (font_set) {
      window->draw(text);
    }
  } else {
    window->draw(textBox);
    if (font_set)
      window->draw(text);
  }

}

void TextArea::setBoxColor(Color c) {
  boxColor = c;
}

string TextArea::getText() {
  return text_input;
}

Vector2f TextArea::getPos() {
  return textBox.getPosition();
}

Vector2f TextArea::getSize() {
  return textBox.getSize();
}

void TextArea::scale(Vector2f oldSize, Vector2f newSize) {
  float x_factor = newSize.x / oldSize.x;
  float y_factor = newSize.y / oldSize.y ;

  textBox.setPosition(textBox.getPosition().x * x_factor, textBox.getPosition().y * y_factor);
  textBox.setSize(Vector2f(textBox.getSize().x * x_factor, textBox.getSize().y * y_factor));

  text.setCharacterSize(text.getCharacterSize() * y_factor);

  if(hasButton)
    updateButton();
  updateText();
}

void TextArea::setError(string s) {
  text_input = "";
  defaultColor = Color(216, 67, 69, 200);
  defaultText = s;
  text.setString(defaultText);
  updateText();

}

void TextArea::setOnlyDigit(bool b) {
  onlyDigit = b;
}
