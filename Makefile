CXX = clang++
SRCDIR = src
BUILDDIR = build
BIN = app

BASEFLAGS = -std=c++20 -MMD -MP

ifeq ($(config),prod)
CXXFLAGS = $(BASEFLAGS) -w -O3
OBJDIR = $(BUILDDIR)/prod
else
CXXFLAGS = $(BASEFLAGS) -Wall -Wextra -g -O0
OBJDIR = $(BUILDDIR)/debug
endif

SRC = $(shell find $(SRCDIR) -name '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

.SILENT:

build: build-debug

build-debug:
	$(MAKE) --no-print-directory $(BIN) config=debug

build-prod:
	$(MAKE) --no-print-directory $(BIN) config=prod

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(BIN)

clean:
	rm -rf $(BUILDDIR) $(BIN)

default: build

-include $(DEP)

.PHONY: default build build-debug build-prod run clean
