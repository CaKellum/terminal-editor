#include <sstream>
#include <string>

const std::string bot_left = "╚";
const std::string top_left = "╔";
const std::string bot_middle = "╩";
const std::string top_middle = "╦";
const std::string left_middle = "╠";
const std::string bottom_top_line = "═";
const std::string middle_middle = "╬";
const std::string right_middle = "╣";
const std::string left_right = "║";
const std::string top_right = "╗";
const std::string bot_right = "╝";

std::string repeat(std::string item, int repeats = 1) {
  std::stringstream ss;
  for (int i = 0; i < repeats; i++) {
    ss << item;
  }
  return ss.str();
}
