#include <sstream>
#include <string>

// MARK: Column functions
std::string rightColumn(int yDelta) {
  std::stringstream ss;
  ss << "\e[" << yDelta << "C";
  return ss.str();
}

std::string leftColumns(int yDelta) {
  std::stringstream ss;
  ss << "\e[" << yDelta << "D";
  return ss.str();
}

std::string moveToColumn(int y) {
  std::stringstream ss;
  ss << "\e[" << y << "G";
  return ss.str();
}

// MARK: Line Functions
std::string upLines(int xDelta) {
  std::stringstream ss;
  ss << "\e[" << xDelta << "A";
  return ss.str();
}

std::string downLines(int xDelta) {
  std::stringstream ss;
  ss << "\e[" << xDelta << "B";
  return ss.str();
}

std::string moveToLine(int x) {
  std::stringstream ss;
  ss << "\e[" << x << "H";
  return ss.str();
}

// MARK: Color functions
enum Color {
  RED,
  YELLOW,
  GREEN,
  BLUE,
  BLACK,
  WHITE,
  MAGENTA,
  CYAN,
  ORANGE,
  VIOLET
};

int ctoi(Color color) {
  int num = 0;
  switch (color) {
  case RED:
    num = 1;
    break;
  case YELLOW:
    num = 3;
    break;
  case GREEN:
    num = 2;
    break;
  case BLUE:
    num = 4;
    break;
  case BLACK:
    num = 0;
    break;
  case WHITE:
    num = 15;
    break;
  case MAGENTA:
    num = 201;
    break;
  case CYAN:
    num = 14;
  case ORANGE:
    num = 210;
    break;
  case VIOLET:
    num = 93;
    break;
  }
  return num;
}

enum Style {
  BOLD,
  DIM,
  ITALIC,
  UNDERLINE,
  BLINK,
  INVERSE,
  HIDDEN,
  STRIKE_THROUGH
};

int styletoi(Style style) {
  int num = 0;
  switch (style) {
  case BOLD:
    num = 1;
    break;
  case DIM:
    num = 2;
    break;
  case ITALIC:
    num = 3;
    break;
  case UNDERLINE:
    num = 4;
    break;
  case BLINK:
    num = 5;
    break;
  case INVERSE:
    num = 7;
    break;
  case HIDDEN:
    num = 8;
    break;
  case STRIKE_THROUGH:
    num = 9;
    break;
  }
  return num;
}

std::string restoreStyling() {
  std::stringstream ss;
  ss << "\e[0m";
  return ss.str();
}

std::string setStyling(Style style) {
  std::stringstream ss;
  ss << "\e[" << styletoi(style) << "m";
  return ss.str();
}

std::string setForegroundColor(Color color) {
  std::stringstream ss;
  ss << "\e[38;5;" << ctoi(color) << "m";
  return ss.str();
}

std::string setBackgroundColor(Color color) {
  std::stringstream ss;
  ss << "\e[48;5;" << ctoi(color) << "m";
  return ss.str();
}
