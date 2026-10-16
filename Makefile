CXX = clang++
CXXFLAGS = -std=c++20
SRC = src/main.cpp
BIN = app

.SILENT:

build: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: build
	./$(BIN)

clean:
	rm -f $(BIN)

default: build

.PHONY: default build run clean
