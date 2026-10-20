#pragma once

#include <sstream>
#include <string>

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

// MARK: Column functions
std::string rightColumn(int yDelta);
std::string leftColumns(int yDelta);
std::string moveToColumn(int y);

// MARK: Line Functions
std::string upLines(int xDelta);
std::string downLines(int xDelta);
std::string moveToLine(int x);

int ctoi(Color color);
int styletoi(Style style);

std::string restoreStyling();
std::string setStyling(Style style);
std::string setForegroundColor(Color color);
std::string setBackgroundColor(Color color);
