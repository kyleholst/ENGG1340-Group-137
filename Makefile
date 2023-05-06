TARGET = scrabble
OBJECTS = dictSearch.o titleScreen.o scorer.o printTile.o displayBoard.o countPoints.o findWords.o makeMove.o scrabble_main.o
FLAGS = -pedantic-errors -std=c++11

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET)

dictSearch.o : dictSearch.cpp functions.h
	g++ $(FLAGS) -c $<

titleScreen.o : titleScreen.cpp functions.h
	g++ $(FLAGS) -c $<

scorer.o : scorer.cpp functions.h
	g++ $(FLAGS) -c $<

printTile.o : printTile.cpp functions.h
	g++ $(FLAGS) -c $<

displayBoard.o : displayBoard.cpp functions.h
	g++ $(FLAGS) -c $<

countPoints.o : countPoints.cpp functions.h
	g++ $(FLAGS) -c $<

findWords.o : findWords.cpp functions.h
	g++ $(FLAGS) -c $<

makeMove.o : makeMove.cpp functions.h
	g++ $(FLAGS) -c $<

scrabble_main.o : scrabble_main.cpp functions.h
	g++ $(FLAGS) -c $<

scrabble: $(OBJECTS)
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean