#include "border_constants.h"
#include "visible_length.h"
using namespace std;

string repeat(string item, int repeats) {
  stringstream ss;
  for (int i = 0; i < repeats; i++) {
    ss << item;
  }
  return ss.str();
}

void _border_edges(int padding, int len, stringstream *ss) {
  for (int i = 0; i < padding; i++) {
    *ss << left_right;
    for (int j = 0; j < (padding + len + padding); j++) {
      *ss << " ";
    }
    *ss << left_right << endl;
  }
}

string border(string str, int padding) {
  int len = str.length();
  int invisible_len = invisibleCount(str);
  int invisible_offset = invisible_len;
  int coloumns = (2 * padding) + len;
  stringstream ss;
  ss << top_left << repeat(bottom_top_line, coloumns) << top_right << endl;
  _border_edges(padding, len, &ss);
  ss << left_right << repeat(" ", padding) << str
     << repeat(" ", padding + invisible_offset) << left_right << endl;
  _border_edges(padding, len, &ss);
  ss << bot_left << repeat(bottom_top_line, coloumns) << bot_right << endl;
  return ss.str();
}
