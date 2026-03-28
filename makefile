CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = garden_db
SOURCES = main.cpp Garden.cpp
HEADERS = Garden.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) *.txt

run: $(TARGET)
	./$(TARGET)

run_custom: $(TARGET)
	./$(TARGET) my_garden.txt

.PHONY: all clean run run_custom
