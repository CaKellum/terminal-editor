#include "includes/asciiconsts.h"
#include "includes/border_constants.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int padding = 10;
  if (argc > 1) {
    padding = atoi(argv[1]);
  }
  stringstream content;
  content << rightColumn(20) << setForegroundColor(RED)
          << setBackgroundColor(GREEN) << "hello" << restoreStyling()
          << setStyling(BLINK) << " world" << restoreStyling();
  cout << border(content.str(), padding) << endl;
  return 0;
}
