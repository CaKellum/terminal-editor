#include "border_constants.h"
#include "visible_length.h"
#include <initializer_list>
using namespace std;

string repeat(string item, int repeats) {
  stringstream ss;
  for (int i = 0; i < repeats; i++) {
    ss << item;
  }
  return ss.str();
}

void border_edges(int padding, int len, stringstream *ss) {
  for (int i = 0; i < padding; i++) {
    *ss << left_right;
    *ss << repeat(" ", (padding * 2) + len);
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
  border_edges(padding, len, &ss);
  ss << left_right << repeat(" ", padding) << str
     << repeat(" ", padding + invisible_offset) << left_right << endl;
  border_edges(padding, len, &ss);
  ss << bot_left << repeat(bottom_top_line, coloumns) << bot_right << endl;
  return ss.str();
}

string multiple_box_border(ContentAlignment alignment,
                           initializer_list<string> strings) {
  stringstream ss;
  int len = strings.size();
  for (int i = 0; i < len; i++) {
    string s = strings.begin()[i];
    int invisible_len = invisibleCount(s);
    bool is_last = (len - 1 == i);
    bool is_first = (0 == i);
    if (is_first) {
      ss << top_left << repeat(bottom_top_line, s.length()) << top_right
         << endl;
    } else {
      ss << left_middle << repeat(bottom_top_line, s.length()) << right_middle
         << endl;
    }
    ss << left_right << s << repeat(" ", invisible_len) << left_right << endl;
    if (is_last) {
      ss << bot_left << repeat(bottom_top_line, s.length()) << bot_right
         << endl;
    }
  }
  return ss.str();
}
