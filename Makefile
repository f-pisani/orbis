# Makefile for Orbis project
CXX = g++
CXXFLAGS = -std=c++11 -Wall -fexceptions -O2 -Ist4code
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Output directories
DEBUG_DIR = debug
RELEASE_DIR = release

# Source files
MAIN_SRC = main.cpp

ORBIS_SRC = Orbis/Game.cpp \
            Orbis/GameOver.cpp \
            Orbis/GraphicsState.cpp \
            Orbis/Menu.cpp \
            Orbis/Orbis.cpp \
            Orbis/Pause.cpp \
            Orbis/Record.cpp

ST4CODE_SRC = st4code/Keyboard.cpp \
              st4code/Mouse.cpp \
              st4code/State.cpp \
              st4code/StateStack.cpp

# All source files
SOURCES = $(MAIN_SRC) $(ORBIS_SRC) $(ST4CODE_SRC)

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
RELEASE_OBJECTS = $(addprefix $(RELEASE_DIR)/, $(OBJECTS))
DEBUG_OBJECTS = $(addprefix $(DEBUG_DIR)/, $(OBJECTS))

# Executable name
TARGET = orbis-game

# Default target
all: release

# Release build
release: CXXFLAGS += -O2
release: $(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)-debug

# Release executable
$(TARGET): $(RELEASE_OBJECTS)
	$(CXX) $(RELEASE_OBJECTS) -o $@ $(LDFLAGS)
	@echo "Release build complete: $@"

# Debug executable
$(TARGET)-debug: $(DEBUG_OBJECTS)
	$(CXX) $(DEBUG_OBJECTS) -o $@ $(LDFLAGS)
	@echo "Debug build complete: $@"

# Pattern rules for object files
$(RELEASE_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR) $(TARGET) $(TARGET)-debug

# Install (copies executable and data files)
install: release
	@echo "Installing Orbis..."
	install -d /usr/local/bin
	install -m 755 $(TARGET) /usr/local/bin/
	install -d /usr/local/share/orbis/data
	cp -r data/* /usr/local/share/orbis/data/

# Run the game
run: release
	./$(TARGET)

# Phony targets
.PHONY: all release debug clean install run