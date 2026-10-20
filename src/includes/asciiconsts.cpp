#include "asciiconsts.h"
using namespace std;

string rightColumn(int yDelta) {
  stringstream ss;
  ss << "\e[" << yDelta << "C";
  return ss.str();
}

string leftColumns(int yDelta) {
  stringstream ss;
  ss << "\e[" << yDelta << "D";
  return ss.str();
}

string moveToColumn(int y) {
  std::stringstream ss;
  ss << "\e[" << y << "G";
  return ss.str();
}

string upLines(int xDelta) {
  std::stringstream ss;
  ss << "\e[" << xDelta << "A";
  return ss.str();
}

string downLines(int xDelta) {
  std::stringstream ss;
  ss << "\e[" << xDelta << "B";
  return ss.str();
}

string moveToLine(int x) {
  std::stringstream ss;
  ss << "\e[" << x << "H";
  return ss.str();
}

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
    break;
  case ORANGE:
    num = 210;
    break;
  case VIOLET:
    num = 93;
    break;
  }
  return num;
}

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

string restoreStyling() {
  stringstream ss;
  ss << "\e[0m";
  return ss.str();
}

string setStyling(Style style) {
  stringstream ss;
  ss << "\e[" << styletoi(style) << "m";
  return ss.str();
}

string setForegroundColor(Color color) {
  stringstream ss;
  ss << "\e[38;5;" << ctoi(color) << "m";
  return ss.str();
}

string setBackgroundColor(Color color) {
  stringstream ss;
  ss << "\e[48;5;" << ctoi(color) << "m";
  return ss.str();
}
