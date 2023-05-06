// scorer.cpp

#include <set>
#include <string>
#include "functions.h"
using namespace std;

int scorer(string tile) {
    int value;
    if (tile.substr(0,5) == "Blank")
        value = 0;
    else if (tile.find_first_of("AEILNORSTU") != -1)
        value = 1;
    else if (tile.find_first_of("DG") != -1)
        value = 2;
    else if (tile.find_first_of("BCMP") != -1)
        value = 3;
    else if (tile.find_first_of("FHVWY") != -1)
        value = 4;
    else if (tile.find_first_of("K") != -1)
        value = 5;
    else if (tile.find_first_of("JX") != -1)
        value = 8;
    else if (tile.find_first_of("QZ") != -1)
        value = 10;
    else
        value = 0;

    return value;
}
