# === Compiler & flags ===
CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra \
            -I./Engine \
            -I./games \
            -I/opt/homebrew/opt/sfml@2/include

# === Linker flags (SFML) ===
LDFLAGS := -L/opt/homebrew/opt/sfml@2/lib \
           -lsfml-graphics -lsfml-window -lsfml-system

# === Source files ===
ENGINE_SRCS := $(wildcard Engine/*.cpp)
SNAKES_SRCS := $(wildcard games/Snakes/*.cpp)
PONG_SRCS   := $(wildcard games/PingPong/*.cpp)
TETRIS_SRCS := $(wildcard games/Tetris/*.cpp)
MAIN_SRC    := src/main.cpp

SRCS := $(ENGINE_SRCS) $(SNAKES_SRCS) $(PONG_SRCS) $(TETRIS_SRCS) $(MAIN_SRC)
OBJS := $(SRCS:.cpp=.o)

# === Target name ===
TARGET := BorgoHub

# === Default rule ===
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Pattern rule: compile .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
