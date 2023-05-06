// dictSearch.cpp

#include "functions.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool dictSearch(string x) {
  // check if a word is in the dictionary of legal words
  string textfile = x.substr(0, 1) + ".txt";
  ifstream f(textfile);
  vector<string> content;
  string line;
  while (getline(f, line)) {
      if (!line.empty() && line.back() == '\r') {
          line.erase(line.size() - 1);
      }
      content.push_back(line);
  }
  bool found=false;
  for (int i=0; i < content.size(); i++) {
      if (content[i] == x) {
          found = true;
          break;
      }
  }
  return found;
}