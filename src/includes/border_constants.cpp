#include "border_constants.h"
#include "visible_length.h"
#include <initializer_list>
using namespace std;

typedef unsigned int uint;

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
  uint len = str.length();
  uint invisible_offset = invisibleCount(str);
  uint coloumns = (2 * padding) + len;
  stringstream ss;
  ss << top_left << repeat(bottom_top_line, coloumns) << top_right << endl;
  border_edges(padding, len, &ss);
  ss << left_right << repeat(" ", padding) << str
     << repeat(" ", padding + invisible_offset) << left_right << endl;
  border_edges(padding, len, &ss);
  ss << bot_left << repeat(bottom_top_line, coloumns) << bot_right << endl;
  return ss.str();
}

uint longest_string_len(initializer_list<string> *strings) {
  uint max = strings->begin()[0].length();
  for (const auto &s : *strings)
    if (max < s.length())
      max = s.length();
  return max;
}

uint cumulative_length_of_n_strings(uint n, initializer_list<string> *strings) {
  uint count = n > strings->size() ? strings->size() : n;
  uint cumulative_length = 0;
  for (uint i = 0; i < count; i++) {
    string s = strings->begin()[i];
    cumulative_length += s.size();
  }
  return cumulative_length;
}

void vertical_border(stringstream *ss, initializer_list<string> *strings) {
  uint len = strings->size();
  uint width = longest_string_len(strings);
  for (uint i = 0; i < len; i++) {
    string s = strings->begin()[i];
    uint invisible_len = invisibleCount(s);
    bool is_last = (len - 1 == i);
    bool is_first = (0 == i);
    uint offset = invisible_len > 0 ? (width - s.length() + invisible_len)
                                    : (width - s.length());
    if (is_first) {
      *ss << top_left << repeat(bottom_top_line, width) << top_right << endl;
    } else {
      *ss << left_middle << repeat(bottom_top_line, width) << right_middle
          << endl;
    }
    *ss << left_right << s << repeat(" ", offset) << left_right << endl;
    if (is_last) {
      *ss << bot_left << repeat(bottom_top_line, width) << bot_right << endl;
    }
  }
}

void horizontal_border(stringstream *ss, initializer_list<string> *strings) {
  uint len = strings->size();
  *ss << top_left;
  for (uint i = 0; i < len; i++) {
    string s = strings->begin()[i];
    *ss << repeat(bottom_top_line, s.length());
    *ss << (i == len - 1 ? top_right : top_middle);
  }
  *ss << endl;
  for (uint i = 0; i < len; i++) {
    string s = strings->begin()[i];
    uint invisible_offset = invisibleCount(s);
    *ss << left_right << s << repeat(" ", invisible_offset);
  }
  *ss << left_right << endl;
  *ss << bot_left;
  for (uint i = 0; i < len; i++) {
    string s = strings->begin()[i];
    *ss << repeat(bottom_top_line, s.length());
    *ss << (i == len - 1 ? bot_right : bot_middle);
  }
}

void diagonal_down_border(stringstream *ss, initializer_list<string> *strings) {
  uint len = strings->size();
  uint last_width = 0;
  for (uint i = 0; i < len; i++) {
    string s = strings->begin()[i];
    uint invisible_offset = invisibleCount(s);
    bool is_last = i == len - 1;
    bool is_first = i == 0;
    *ss << (is_first ? top_left : "") << repeat(bottom_top_line, s.length())
        << top_right << endl;
    *ss << repeat(" ", last_width) << left_right << s
        << repeat(" ", invisible_offset) << left_right << "\n";
    *ss << repeat(" ", last_width) << bot_left
        << repeat(bottom_top_line, s.length())
        << (is_last ? bot_right : middle_middle);
    if (is_last)
      *ss << endl;
    last_width = 1 + s.length() + last_width;
  }
}

void diagonal_up_border(stringstream *ss, initializer_list<string> *strings) {
  uint len = strings->size();
  uint last_width = 0;
  uint initial_offset = cumulative_length_of_n_strings(len - 1, strings);
  for (uint i = (len - 1); i > 0; i--) {
    bool is_first = (i == len - 1);
    bool is_last = (i == 0);
    string s = strings->begin()[i];
    *ss << repeat(" ", initial_offset) << (is_first ? top_left : middle_middle)
        << repeat(bottom_top_line, (s.size() + 2))
        << (is_first ? top_right : middle_middle) << endl;
    *ss << repeat(" ", initial_offset) << left_right << " " << s << " "
        << left_right << endl;
    *ss << repeat(" ", initial_offset) << (is_last ? bot_left : middle_middle)
        << repeat(bottom_top_line, (s.size() + 2)) << endl;
    initial_offset = cumulative_length_of_n_strings(i, strings);
  }
}

string multiple_box_border(ContentAlignment alignment,
                           initializer_list<string> strings) {
  stringstream ss;
  if (alignment == VERTICAL) {
    vertical_border(&ss, &strings);
  } else if (alignment == HORIZONTAL) {
    horizontal_border(&ss, &strings);
  } else if (alignment == DIAGONAL_DOWN) {
    diagonal_down_border(&ss, &strings);
  } else if (alignment == DIAGONAL_UP) {
    diagonal_up_border(&ss, &strings);
  }
  return ss.str();
}
