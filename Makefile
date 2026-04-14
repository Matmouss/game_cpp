CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -O0
LDFLAGS = -lncurses

TARGET = test
SRC = main.cpp entite.cpp affichage.cpp act.cpp csv.cpp monstre.cpp personnage.cpp partie.cpp item.cpp stat.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)