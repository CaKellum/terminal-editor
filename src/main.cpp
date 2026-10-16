#include "includes/asciiconsts.h"
#include "includes/border_constants.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  cout << top_left << repeat(bottom_top_line, 50) << top_right << endl;
  cout << repeat(left_right + rightColumn(50) + left_right + "\n", 5);
  cout << left_right << rightColumn(20) << setForegroundColor(RED)
       << setBackgroundColor(GREEN) << "hello" << restoreStyling()
       << setStyling(BLINK) << " world" << restoreStyling() << rightColumn(19)
       << left_right << endl;
  cout << repeat(left_right + rightColumn(50) + left_right + "\n", 5);
  cout << bot_left << repeat(bottom_top_line, 50) << bot_right << endl;
  return 0;
}
