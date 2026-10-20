CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -MMD -MP
SRCDIR = src
BUILDDIR = build
BIN = app

SRC = $(shell find $(SRCDIR) -name '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

.SILENT:

build: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(BIN)

clean:
	rm -rf $(BUILDDIR) $(BIN)

default: build

-include $(DEP)

.PHONY: default build run clean
