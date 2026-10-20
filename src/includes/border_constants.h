#pragma once

#include <cstdio>
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

enum ContentAlignment { VERTICAL, HORIZONTAL, DIAGONAL_DOWN, DIAGONAL_UP };

enum PlacmentPreference { LEADING, TRAILING, TOP, BOTTOM };

struct PositionData {
  ContentAlignment preffered_alignment;
  PlacmentPreference prefered_placments[];
};

std::string repeat(std::string item, int repeats = 1);
void _border_edges(int padding, int len, std::stringstream *ss);
std::string border(std::string str, int padding = 1);
